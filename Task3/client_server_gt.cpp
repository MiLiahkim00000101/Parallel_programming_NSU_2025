#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <ctime>
#include <cstdlib>
#include <stop_token>
#include <utility>
#include <unordered_map>
#include <random>
#include <sstream>
#include <cassert>
#include <iomanip>

template<typename T>
T fun_sin(T arg) {
    return std::sin(arg);
}

template<typename T>
T fun_sqrt(T arg) {
    return std::sqrt(arg);
}

template<typename T>
T fun_pow(T x, T y) {
    return std::pow(x, y);
}

class Server {
private:
    std::queue<std::tuple<std::packaged_task<double()>, size_t, std::string, double, double>> tasks;
    size_t task_id = 0;
    std::unordered_map<size_t, double> results;
    std::stop_source stop_source;
    std::mutex mut;
    std::condition_variable cond_var;
    std::ofstream file_out;
    std::atomic<size_t> tasks_in_progress{0};  // Добавляем счетчик задач
    std::atomic<bool> all_tasks_added{false};  // Флаг завершения добавления

public:

    Server(){};

    int get_queue_size(){
        return tasks.size();
    }

    void start() {
        auto stop_token = stop_source.get_token();
        file_out.open("out_server_log.csv");
        file_out << "id,operation,arg1,arg2,result" << std::endl;
        while (true) {
            std::unique_lock<std::mutex> lock(mut);
            cond_var.wait(lock, [this, &stop_token]() {
                return !tasks.empty() || stop_token.stop_requested();
            });

            if (stop_token.stop_requested()) {
                break;
            }

            if (!tasks.empty()) {
                auto task = std::move(tasks.front());
                tasks.pop();
                tasks_in_progress++;
                lock.unlock();

                auto& packaged_task = std::get<0>(task);
                size_t task_id_curr = std::get<1>(task);
                std::string operation = std::get<2>(task);

                packaged_task();
                std::future<double> result = packaged_task.get_future();
                double result_value = result.get();

                {
                    std::lock_guard<std::mutex> res_lock(mut);
                    results[task_id_curr] = result_value;
                }

                // std::cout << "task_id: " << task_id_curr
                //           << " operation: " << operation
                //           << " result: " << result_value << std::endl;
                
                // В методе start() при записи в файл
                file_out << task_id_curr << ","
                << operation << ","
                << std::fixed << std::setprecision(15) << std::get<3>(task) << ","
                << std::fixed << std::setprecision(15) << std::get<4>(task) << ","
                << std::fixed << std::setprecision(15) << result_value << std::endl;

                tasks_in_progress--;
            }
        }
        std::cout << "Server stopped" << std::endl;
    }

    void stop() {
        stop_source.request_stop();
        cond_var.notify_all();
        file_out.close();
    }

    size_t add_task(std::tuple<std::string, double, double> task_info) {
        std::string operation = std::get<0>(task_info);
        std::packaged_task<double()> task;

        if (operation == "sin") {
            double arg = std::get<1>(task_info);
            task = std::packaged_task<double()>(std::bind(fun_sin<double>, arg));
        } else if (operation == "pow") {
            double x = std::get<1>(task_info);
            double y = std::get<2>(task_info);
            task = std::packaged_task<double()>(std::bind(fun_pow<double>, x, y));
        } else if (operation == "sqrt") {
            double arg = std::get<1>(task_info);
            task = std::packaged_task<double()>(std::bind(fun_sqrt<double>, arg));
        } else {
            return -1;
        }

        size_t current_id;
        {
            std::lock_guard<std::mutex> lock(mut);
            current_id = task_id++;
            tasks.emplace(std::move(task), current_id, operation, std::get<1>(task_info), std::get<2>(task_info));
        }
        cond_var.notify_one();
        return current_id;
    }

    double request_result(size_t id_res) {
        /*
        If id_res in available range -> result of task with given id
        else -> -1
        */
        std::lock_guard<std::mutex> lock(mut);
        auto it = results.find(id_res);
        return (it != results.end()) ? it->second : -1.0f;
    }

    void wait_all() {
        while (!tasks.empty() || tasks_in_progress > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            // можно выполнять другие важные задачи. В том числе сделать вариацию threadpool'a
        }
    }

    void signal_all_tasks_added() {
        all_tasks_added = true;
    }
};

void Test(){
    std::ifstream file_in("out_server_log.csv", std::ios::in);

    std::vector<int> ids_row;
    std::vector<double> arg1_row;
    std::vector<double> arg2_row;
    std::vector<double> answer_row;
    std::vector<std::string> operation_row;
    std::string line;
    constexpr double EPS = 1e-9;
    int i = 0; // iterator on cells in csv
    std::getline(file_in, line); // string with csv information
    while(std::getline(file_in, line)){
        std::stringstream lineStream(line);
        char cell[100];
        while(lineStream.getline(cell, 100, ',')){
            if (i == 0) // id
                ids_row.push_back(atoi(cell));
            if (i == 1) // operation
                operation_row.push_back(cell);
            if (i == 2) // arg1
                arg1_row.push_back(atof(cell));
            if (i == 3) // arg2
                arg2_row.push_back(atof(cell));
            if (i == 4) // result
                answer_row.push_back(atof(cell));
            i++;
        }
        i = 0;
    }
    for (int j = 0; j < ids_row.size(); j++){
        //std::cout << ids_row[j] << "," << operation_row[j] << "," << arg1_row[j] << "," << arg2_row[j] << "," << answer_row[j] << std::endl;
        
        if (operation_row[j] == "sin"){
            //std::cout << fabs(sin(arg1_row[j])) - fabs(answer_row[j]) << "    " << (sin(arg1_row[j]) == answer_row[j]) << std::endl;
            assert(fabs(sin(arg1_row[j])) - fabs(answer_row[j]) < EPS);
        }
        if (operation_row[j] == "sqrt"){
            //std::cout << sqrt(arg1_row[j]) << "==" << answer_row[j] << std::endl;
            assert(fabs(sqrt(arg1_row[j])) - fabs(answer_row[j]) < EPS);
        }
        if (operation_row[j] == "pow"){
            //std::cout << pow(arg1_row[j], arg2_row[j]) << "==" << answer_row[j] << std::endl;
            //std::cout << "first: " << fabs(pow(arg1_row[j], arg2_row[j])) << " second: " << fabs(answer_row[j]) << " diff = " << fabs(pow(arg1_row[j], arg2_row[j])) - fabs(answer_row[j]) << std::endl;
            assert(fabs(pow(arg1_row[j], arg2_row[j])) - fabs(answer_row[j]) < EPS);
        }
        
    }
    

}

int main() {
    Server serv;
    std::thread server_thread([&serv]() { serv.start(); });

    auto client_lambda = [](const char* op, Server& s) {
        std::mt19937 mt(time(nullptr));
        int num_of_iter = mt() % 9996 + 5;
        for (int i = 0; i < num_of_iter; ++i) {
            double arg1 = (double) (rand() % 50) / 1000;
            double arg2;
            if (op == "pow")
                arg2 = rand() % 3;
            else
                arg2 = 0;
            s.add_task({op, arg1, arg2});
        }
    };

    std::thread client_sin(client_lambda, "sin", std::ref(serv));
    std::thread client_pow(client_lambda, "pow", std::ref(serv));
    std::thread client_sqrt(client_lambda, "sqrt", std::ref(serv));

    client_sin.join();
    client_pow.join();
    client_sqrt.join();

    serv.signal_all_tasks_added();


    serv.wait_all();

    double res_0 = serv.request_result(0);

    serv.stop();
    server_thread.join();
    std::cout << res_0 << std::endl;

    Test();

    return 0;
}