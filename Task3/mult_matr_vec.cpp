#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "tqdm.hpp"



// File management functions
std::ofstream file_vec_matr_mult_20000;
std::ofstream file_vec_matr_mult_40000;

//---------------------------------------------------------------------------------

void openFiles() {
    file_vec_matr_mult_20000.open("res_mult_20000.csv", std::ios::app);
    file_vec_matr_mult_40000.open("res_mult_40000.csv", std::ios::app);

    if (!file_vec_matr_mult_20000.is_open())
        std::cerr << "Ошибка открытия res_mult_20000.csv!" << std::endl;
    if (!file_vec_matr_mult_40000.is_open())
        std::cerr << "Ошибка открытия res_mult_40000.csv!" << std::endl;
    
    file_vec_matr_mult_20000 << "Amount_of_threads;Time_of_execution;Speedup" << std::endl;
    file_vec_matr_mult_40000 << "Amount_of_threads;Time_of_execution;Speedup" << std::endl;
     
}
//---------------------------------------------------------------------------------

void closeFiles() {
    file_vec_matr_mult_20000.close();
    file_vec_matr_mult_40000.close();
}
//---------------------------------------------------------------------------------

void clearFiles() {
    std::ofstream clearFile;

    clearFile.open("res_mult_20000.csv", std::ios::trunc);
    clearFile.close();

    clearFile.open("res_mult_40000.csv", std::ios::trunc);
    clearFile.close();

    std::cout << "Файлы очищены." << std::endl;
}

//---------------------------------------------------------------------------------

// Functions for working with time
double start_time;
double end_time;
//---------------------------------------------------------------------------------

double Start_Clock(){
    start_time =  std::chrono::duration_cast<std::chrono::duration<double>>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
    return start_time;
}
//---------------------------------------------------------------------------------

double Check_Clock(){
    end_time =  std::chrono::duration_cast<std::chrono::duration<double>>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
    return end_time - start_time;
}
//---------------------------------------------------------------------------------


// Однопоточная версия
void matrix_vector_product(double* a, double* b, double* c, int m, int n) {
    for (int i = 0; i < m; ++i) {
        c[i] = 0;
        for (int j = 0; j < n; ++j) {
            c[i] += a[i * n + j] * b[j];
        }
    }
}
//---------------------------------------------------------------------------------

// Многопоточная версия
void matrix_vector_thread_worker(double* a, double* b, double* c, int m, int n, int start_row, int end_row) {
    for (int i = start_row; i < end_row; ++i) {
        c[i] = 0;
        for (int j = 0; j < n; ++j) {
            c[i] += a[i * n + j] * b[j];
        }
    }
}
//---------------------------------------------------------------------------------

void matrix_vector_product_threads(double* a, double* b, double* c, int m, int n, int n_threads) {
    std::vector<std::thread> threads;
    int rows_per_thread = m / n_threads;
    int extra_rows = m % n_threads;

    int current_row = 0;
    for (int t = 0; t < n_threads; ++t) {
        int start_row = current_row;
        int end_row = start_row + rows_per_thread + (t < extra_rows ? 1 : 0);
        threads.emplace_back(matrix_vector_thread_worker, a, b, c, m, n, start_row, end_row);
        current_row = end_row;
    }

    for (auto& t : threads)
        t.join();
}
//---------------------------------------------------------------------------------
void initialize_worker(double* a, double* v, double* c, int size, int start_row, int end_row){
    for (int i = start_row; i < end_row; ++i){
        c[i] = 0;
        v[i] = i;

        for (int j = 0; j < size; ++j){
            a[i * size + j] = i * size + j;
        }
    }
}
//---------------------------------------------------------------------------------

void Init_of_containers(double* a, double* v, double* c, int size, int n_threads){
    std::vector<std::thread> threads;
    int rows_per_thread = size / n_threads;
    int extra_rows = size % n_threads;

    int current_row = 0;
    for (int t = 0; t < n_threads; ++t){
        int start_row = current_row;
        int end_row = start_row + rows_per_thread + (t < extra_rows ? 1 : 0);
        threads.emplace_back(initialize_worker, a, v, c, size, start_row, end_row );
        current_row = end_row;
    }

    for (auto &t : threads){
        t.join();
    }

}
//---------------------------------------------------------------------------------

// for matrix_vector_multiplication
int Num_Threads[5] = {1, 2, 4, 7, 8};
int Matrix_Sizes[2] = {20000, 40000};

double time_of_exec;
double result_time;
double result_one_thread_time_sz_20000;
double result_one_thread_time_sz_40000;

//---------------------------------------------------------------------------------
int main(){
    clearFiles();
    openFiles();

    int num_of_mult = 0;

    for (int n_threads : Num_Threads){
        for (int m_size : Matrix_Sizes){
            result_time = 0;
            std::cout << std::endl;
            std::cout << "This is " << ++num_of_mult << " multiplication!" << std::endl;
            for (int k : tq::trange(5)){
                
                std::vector<double> a(m_size * m_size);
                std::vector<double> b(m_size);
                std::vector<double> c(m_size);

                std::vector<double>::iterator it_a = a.begin();
                std::vector<double>::iterator it_b = a.begin();
                std::vector<double>::iterator it_c = a.begin();

                double * pt_a = &(* it_a);
                double * pt_b = &(* it_b);
                double * pt_c = &(* it_c);

                Init_of_containers(pt_a, pt_b, pt_c, m_size, n_threads);

                Start_Clock();
                
                matrix_vector_product_threads(pt_a, pt_b, pt_c, m_size, m_size, n_threads);

                time_of_exec = Check_Clock();

                result_time += time_of_exec;

            }

            if (n_threads == 1 && m_size == 20000)
                result_one_thread_time_sz_20000 = result_time / 5;
            else if (n_threads == 1 && m_size == 40000)
                result_one_thread_time_sz_40000 = result_time / 5;

            result_time /= 5;

            if (m_size == 20000)
                file_vec_matr_mult_20000 << n_threads << ";" << result_time << ";" << result_one_thread_time_sz_20000/result_time << std::endl;
            else
                file_vec_matr_mult_40000 << n_threads << ";" << result_time << ";" << result_one_thread_time_sz_40000/result_time << std::endl;
            
        }
    }

}