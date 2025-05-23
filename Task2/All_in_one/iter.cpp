#include <iostream>
#include <vector>
#include <omp.h>
#include <cmath>
#include <chrono>
#include <fstream>

// Функция для параллельного заполнения матрицы и вектора
void fill_matrix_vector(std::vector<std::vector<double>> &A, std::vector<double> &b, int N, int n_threads) {
    #pragma omp parallel num_threads(n_threads)
    {
        int nthreads = n_threads;
        int threadid = omp_get_thread_num();
        int items_per_thread = N/n_threads;
        int lb = threadid * items_per_thread;
        int ub = (threadid == nthreads - 1) ? (N - 1) : (lb + items_per_thread - 1);

        for (int i = lb; i <= ub; ++i) {
            b[i] = N + 1;  
            for (int j = 0; j < N; ++j) {
                A[i][j] = (i == j) ? 2.0 : 1.0;  
            }
        }
    }
    
}

void res_init(std::vector<double> &x, int n_threads, int N){
    #pragma omp parallel num_threads(n_threads)
    {
        int nthreads = n_threads;
        int threadid = omp_get_thread_num();
        int items_per_thread = N / nthreads;
        int lb = threadid * items_per_thread;
        int ub = (threadid == nthreads - 1) ? (N - 1) : (lb + items_per_thread - 1 );

        for (int i = lb; i < ub; i++){
            x[i] = 0.0;
        }
    }
}

// Функция для вычисления нормы вектора
double norm(const std::vector<double> &vec, int N) {
    double result = 0.0;
    for (int i = 0; i < N; ++i) {
        result += vec[i] * vec[i];
    }
    return std::sqrt(result);
}

// Метод градиентного спуска для решения системы Ax = b с отдельными секциями #pragma omp for
void gradient_descent_separate_sections(const std::vector<std::vector<double>> &A, const std::vector<double> &b, std::vector<double> &x, int N, double tau, int max_iter, int n_threads, double epsilon) {
    std::vector<double> residual(N);  // Вектор ошибки A*x - b
    std::vector<double> Ax(N);        // Вектор A*x

    // Инициализация решения (можно начинать с нулевого вектора)
    res_init(x, n_threads, N);
    /*for(int i = 0; i < N; ++i){
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;
    */
   int iter = 0;
   double relative_residual;


    // Итерации метода градиентного спуска
    for (int iter = 0; iter < max_iter; ++iter) {
        // Вычисление Ax
        #pragma omp parallel for num_threads(n_threads)
        for (int i = 0; i < N; ++i) {
            Ax[i] = 0.0;
            for (int j = 0; j < N; ++j) {
                Ax[i] += A[i][j] * x[j];
            }
        }

        // Вычисление остатка A*x - b
        #pragma omp parallel for num_threads(n_threads)
        for (int i = 0; i < N; ++i) {
            residual[i] = Ax[i] - b[i];
        }

        // Обновление x: x^{n+1} = x^n - tau * (Ax^n - b)
        #pragma omp parallel for num_threads(n_threads)
        for (int i = 0; i < N; ++i) {
            x[i] -= tau * residual[i];
        }

        // Проверка критерия завершения ||Ax^n - b|| / ||b|| < epsilon
        double residual_norm = norm(residual, N);
        double b_norm = norm(b, N);
        double relative_residual = residual_norm / b_norm;

        if (relative_residual < epsilon) {
            std::cout << "Завершение на итерации " << iter + 1 << " с относительной нормой остатка " << relative_residual << std::endl;
            return;
        }
    }
    std::cout << "Завершение на итерации " << iter + 1 << " с относительной нормой остатка " << relative_residual << std::endl;
    return;

    

}

// Метод градиентного спуска для решения системы Ax = b с одной параллельной секцией #pragma omp parallel
void gradient_descent_single_parallel_section(const std::vector<std::vector<double>> &A, const std::vector<double> &b, std::vector<double> &x, int N, double tau, int max_iter, int n_threads, double epsilon) {
    std::vector<double> residual(N);  // Вектор ошибки A*x - b
    std::vector<double> Ax(N);        // Вектор A*x

    // Инициализация решения (можно начинать с нулевого вектора)
    res_init(x, n_threads, N);

    double relative_residual;
    // Итерации метода градиентного спуска
    int iter = 0;
    for (iter; iter < max_iter; ++iter) {
        #pragma omp parallel num_threads(n_threads)
        {
            int nthreads = n_threads;
            int threadid = omp_get_thread_num();
            int items_per_thread = N/n_threads;
            int lb = threadid * items_per_thread;
            int ub = (threadid == nthreads - 1) ? (N - 1) : (lb + items_per_thread);

            for (int i = lb; i < ub; ++i){
                Ax[i] = 0.0;
                for (int j = 0; j < N; ++j) {
                    Ax[i] += A[i][j] * x[j];
                }
            }

            // Вычисление Ax
            /*#pragma omp for
            for (int i = 0; i < N; ++i) {
                Ax[i] = 0.0;
                for (int j = 0; j < N; ++j) {
                    Ax[i] += A[i][j] * x[j];
                }
            }*/

            // Вычисление остатка A*x - b
            #pragma omp for
            for (int i = 0; i < N; ++i) {
                residual[i] = Ax[i] - b[i];
            }

            // Обновление x: x^{n+1} = x^n - tau * (Ax^n - b)
            #pragma omp for
            for (int i = 0; i < N; ++i) {
                x[i] -= tau * residual[i];
            }
        }

        // Проверка критерия завершения ||Ax^n - b|| / ||b|| < epsilon
        double residual_norm = norm(residual, N);
        double b_norm = norm(b, N);
        relative_residual = residual_norm / b_norm;

        if (relative_residual < epsilon) {
            std::cout << "Завершение на итерации " << iter + 1 << " с относительной нормой остатка " << relative_residual << std::endl;
            return;
        }
    }
    std::cout << "Завершение на итерации " << iter + 1 << " с относительной нормой остатка " << relative_residual << std::endl;
    return;
}

int main() {
    int N = 2000;  // Размер матрицы и вектора
    int max_iter = 1000;  // Максимальное количество итераций
    double tau = 0.01;  // Параметр шага
    double epsilon = 1e-5;  // Погрешность для критерия завершения
    int Num_Threads[8] = {1, 2, 4, 7, 8, 16, 20, 40};  // Массив с количеством потоков

    // Инициализация матрицы A (размер N x N) и вектора b (размер N)
    std::vector<std::vector<double>> A(N, std::vector<double>(N));
    std::vector<double> b(N);
    std::vector<double> x(N, 0.0);  // Начальные значения вектора x — 0
    // переменная, которая покажет какой по счету раз мы считаем решение
    int num_of_solution = 1;

    /*
    for(int i = 0; i < N; ++i){
        std::cout << i << ": ";
        for (int j = 0; j < N; ++j){
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }*/

    // Открываем файлы для записи результатов
    std::ofstream file_for_omp("iter_for_omp_res.csv");
    file_for_omp << "Amount_of_threads;Time_of_execution;Speedup\n";

    std::ofstream file_omp("iter_omp_res.csv");
    file_omp << "Amount_of_threads;Time_of_execution;Speedup\n";

    // Замер времени для одного потока
    std::chrono::duration<double> duration_1_thread{0};

    for (int i = 0; i < 10; ++i){
        fill_matrix_vector(A, b, N, 1);
        std::cout << num_of_solution++ << ": " << std::endl;
        auto start_time_1_thread = std::chrono::high_resolution_clock::now();
        gradient_descent_separate_sections(A, b, x, N, tau, max_iter, 1, epsilon);
        auto end_time_1_thread = std::chrono::high_resolution_clock::now();
        duration_1_thread += end_time_1_thread - start_time_1_thread;
    }

    duration_1_thread /=  10;
    
    double time_1_thread = duration_1_thread.count();  // Время выполнения для 1 потока
    //std::cout << std::endl << "Time for 1 thread: " << time_1_thread << std::endl;
    //return 0;

    // Пройдем по каждому количеству потоков и замерим время выполнения
    for (int i = 0; i < 8; ++i) {
        int n_threads = Num_Threads[i];
        std::chrono::duration<double> duration{0};
        for(int j = 0; j < 10; ++j){
            // Замер времени для первой реализации (отдельные параллельные секции для каждого цикла)
            fill_matrix_vector(A, b, N, n_threads);
            std::cout << num_of_solution++ << ": " << std::endl;
            auto start_time = std::chrono::high_resolution_clock::now();
            gradient_descent_separate_sections(A, b, x, N, tau, max_iter, n_threads, epsilon);
            auto end_time = std::chrono::high_resolution_clock::now();
            duration += end_time - start_time;
        }

        duration /= 10;
       
        double speedup = time_1_thread / duration.count();  // Вычисление ускорения
        file_for_omp << n_threads << ";" << duration.count() << ";" << speedup << "\n";
        /*std::cout << "Separate section: \n";
        std::cout << "Answer " << i << "is " << std::endl;
        for(int i = 0; i < N; ++i){
            std::cout << x[i] << " ";
        }
        std::cout << std::endl << std::endl;   */

        std::chrono::duration<double> duration1{0};
        for(int j = 0; j < 10; ++j){
            // Замер времени для второй реализации (одна параллельная секция охватывает весь цикл)
            fill_matrix_vector(A, b, N, n_threads);
            std::cout << num_of_solution++ << ": " << std::endl;
            auto start_time = std::chrono::high_resolution_clock::now();
            gradient_descent_single_parallel_section(A, b, x, N, tau, max_iter, n_threads, epsilon);
            auto end_time = std::chrono::high_resolution_clock::now();
            duration1 += end_time - start_time;
        }

        duration1 /= 10;
        
        speedup = time_1_thread / duration1.count();  // Вычисление ускорения
        file_omp << n_threads << ";" << duration1.count() << ";" << speedup << "\n";

        /*std::cout << "For section: \n";
        std::cout << "Answer " << i << "is " << std::endl;
        for(int i = 0; i < N; ++i){
            std::cout << x[i] << " ";
        }
        std::cout << std::endl << std::endl;   */
    }

    // Закрытие файлов
    file_for_omp.close();
    file_omp.close();

    std::cout << "Результаты записаны в iter_for_omp_res.csv и iter_omp_res.csv" << std::endl;

    return 0;
}
