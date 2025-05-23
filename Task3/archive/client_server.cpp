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




//---------------------------------------------------------------------------------
template<typename T>
T fun_sin(T arg){
    return std::sin(arg);
}
//---------------------------------------------------------------------------------

template<typename T>
T fun_sqrt(T arg){
    return std::sqrt(arg);
}
//---------------------------------------------------------------------------------

template<typename T>
T fun_pow(T x, T y){
    return std::pow(x, y);
}
//---------------------------------------------------------------------------------


class Server{
private:

    std::queue<std::tuple<std::packaged_task<float()>, size_t, std::string>> tasks;
    std::tuple<std::packaged_task<float()>, size_t, std::string> task;
    size_t task_id = 0;
    std::unordered_map<size_t, float> results;
    std::stop_token stoken;
    std::mutex mut;
    std::condition_variable cond_var;


public:
    Server(std::stop_token from_main_stoken){
        stoken = from_main_stoken;
    };
    ~Server(){};
    void start(std::stop_token &stoken){

        while(!stoken.stop_requested()){
            std::unique_lock<std::mutex> lock(mut, std::defer_lock);
            lock.lock();
            cond_var.wait(lock, [&stoken] (auto tasks) { return !tasks.empty() || stoken.stop_requested(); });
            
            if (stoken.stop_requested())
                stop();

            if (!tasks.empty()){
                task = std::move(tasks.front());
                tasks.pop();
                lock.unlock();
                std::future<float> result = (std::get<0>(task)).get_future(); 
                size_t task_id_curr = std::get<1>(task);
                std::get<0>(task)();
                result.wait();
                results.insert({task_id, result.get()});
                std::cout << "task_id: " << task_id_curr << "operation: " << std::get<2>(task);
            }
        
        }
        
    }
    void stop(){
        stoken.stop_requested();
        std::cout << "Server stopped" << std::endl;
    }

    size_t add_task(std::tuple<std::string, double, double> task_info){

        std::packaged_task<float()> task;
        std::string operation;

        switch(std::get<0>(task_info)[1]){
            case 'i': // second letter of word "sin"
                task = std::packaged_task<float()> (std::bind(fun_sin<float>, std::get<1>(task_info)));
                operation = "sin";
                break;
            case 'o': // second letter of word "pow"
                task = std::packaged_task<float()> (std::bind(fun_pow<float>, std::get<1>(task_info), std::get<2>(task_info)));
                operation = "pow";
                break;
            case 'q': // second letter of word "sqrt"
                task = std::packaged_task<float()> (std::bind(fun_sqrt<float>, std::get<1>(task_info)));
                operation = "sqrt";
                break;
            default:
                return -1;
            
        }

        {
            std::lock_guard<std::mutex> lock(mut);
            std::tuple<std::packaged_task<float()>, size_t, std::string> temp_task(std::move(task), task_id, operation);
            tasks.push(temp_task); // Добавляем задачу в очередь
        }

        cond_var.notify_one(); // Уведомляем другой поток о добавлении новой задачи

        return task_id++;
        
    }
    
    float request_result(size_t id_res){
        float result;

        return result;
    }
};

using namespace std::chrono_literals;


int main(){

    // установим рандом
    time_t t = time(NULL);
    srand(t);
    
    Server serv;
    std::stop_token stoken;
    serv.start(stoken);

    std::thread client_sin([](Server& serv){for(int i = 0; i < rand() % 9994 + 6; ++i) serv.add_task({"sin", rand(), 0});});
    std::thread client_pow([](Server& serv){for(int i = 0; i < rand() % 9994 + 6; ++i) serv.add_task({"pow", rand(), 0});});
    std::thread client_sqrt([](Server& serv){for(int i = 0; i < rand() % 9994 + 6; ++i) serv.add_task({"sqrt", rand(), 0});});

    serv.stop();



    return 0;

}