#include <iostream>
#include <fstream>
#include <omp.h>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <cmath>
#include <string>




double func(double x)
{
    return exp(-x * x); 
}
double integrate(double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += func(a + h * (i + 0.5));
    sum *= h;
    return sum;
}

double integrate_omp(double (*func)(double), double a, double b, int n, int n_threads)
{
    double h = (b - a) / n;
    double sum = 0.0;
    #pragma omp parallel num_threads(n_threads)
    {
        int nthreads = n_threads;
        int threadid = omp_get_thread_num();
        int items_per_thread = n / nthreads;
        int lb = threadid * items_per_thread;
        int ub = (threadid == nthreads - 1) ? (n - 1) : (lb + items_per_thread - 1);
        double sumloc = 0.0;
        for (int i = lb; i <= ub; i++)
            sumloc += func(a + h * (i + 0.5));
        #pragma omp atomic
        sum += sumloc;
    }
    sum *= h;
    return sum;
}


void matrix_vector_product_omp(double *a, double *b, double *c, int m, int n, int n_threads)
{
    #pragma omp parallel num_threads(n_threads)
    {
        int nthreads = n_threads;
        int threadid = omp_get_thread_num();
        int items_per_thread = m / nthreads;
        int lb = threadid * items_per_thread;
        int ub = (threadid == nthreads - 1) ? (m - 1) : (lb + items_per_thread - 1);

        for (int i = lb; i <= ub; ++i){
            c[i] = 0;
            for (int j = 0; j < n; ++j){
                // Memory ops: Load c[i], Load a[i][j], Load b[j], Store c[i]
                c[i] += a[i * n + j] * b[j];
            }
        }
    }
}

void matrix_vector_product(double *a, double *b, double *c, int m, int n)
{
    for (int i = 0; i < m; ++i){
        c[i] = 0;
        for (int j = 0; j < n; ++j){
            c[i] += a[i * n + j] * b[j];
        }
    }
}


double start_time;
double end_time;

double Start_Clock(){
    start_time =  std::chrono::duration_cast<std::chrono::duration<double>>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
    return start_time;
}
double Stop_Clock(){
    end_time =  std::chrono::duration_cast<std::chrono::duration<double>>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
    return end_time;
}

std::ofstream file_vec_matr_mult_20000;
std::ofstream file_vec_matr_mult_40000;
std::ofstream file_integr_40000000;

void openFiles() {
    file_vec_matr_mult_20000.open("res_mult_20000.csv", std::ios::app);
    file_vec_matr_mult_40000.open("res_mult_40000.csv", std::ios::app);
    file_integr_40000000.open("res_integr_40000000.csv", std::ios::app);

    if (!file_vec_matr_mult_20000.is_open())
        std::cerr << "Ошибка открытия res_mult_20000.csv!" << std::endl;
    if (!file_vec_matr_mult_40000.is_open())
        std::cerr << "Ошибка открытия res_mult_40000.csv!" << std::endl;
    if (!file_integr_40000000.is_open())
        std::cerr << "Ошибка открытия res_integr_40000000.csv!" << std::endl;
}

void closeFiles() {
    file_vec_matr_mult_20000.close();
    file_vec_matr_mult_40000.close();
    file_integr_40000000.close();
}

void clearFiles() {
    std::ofstream clearFile;

    clearFile.open("res_mult_20000.csv", std::ios::trunc);
    clearFile.close();

    clearFile.open("res_mult_40000.csv", std::ios::trunc);
    clearFile.close();

    clearFile.open("res_integr_40000000.csv", std::ios::trunc);
    clearFile.close();

    std::cout << "Файлы очищены." << std::endl;
}


#include <memory>

// for integral
const double a = -4.0;
const double b = 4.0;
const int nsteps = 40000000;
// for integral

// for matrix_vector_multiplication
int Num_Threads[8] = {1, 2, 4, 7, 8, 16, 20, 40};
int Matrix_Sizes[2] = {20000, 40000};
// for matrix_vector_multiplication


int main(){

    clearFiles();   // open and clear
                    // res_mult_20000.csv
                    // res_mult_40000.csv
                    // res_integr_40000000.csv

    openFiles();    // open 
                    // res_mult_20000.csv
                    // res_mult_40000.csv
                    // res_integr_40000000.csv

    /*
        Now  opened:
        std::ofstream file_vec_matr_mult_20000;
        std::ofstream file_vec_matr_mult_40000;
        std::ofstream file_integr_40000000;         
    */
   file_integr_40000000 << "Amount_of_threads;Time_of_execution;Speedup" << std::endl;
   file_vec_matr_mult_20000 << "Amount_of_threads;Time_of_execution;Speedup" << std::endl;
   file_vec_matr_mult_40000 << "Amount_of_threads;Time_of_execution;Speedup" << std::endl;

   double time_of_exec;
   double result_time;
   double one_thread_time;
   double result_one_thread_time_sz_20000;
   double result_one_thread_time_sz_40000;




   // count first part of multiplying matrix on vector

    for (int n_threads : Num_Threads){
        for (int matr_sz : Matrix_Sizes){
            // start counting time

            std::unique_ptr<double []> a{std::make_unique<double[]>(matr_sz * matr_sz)},
                v{std::make_unique<double[]>(matr_sz)}, c{std::make_unique<double[]>(matr_sz)};
            
            result_time = 0;

            for (int i = 0; i < 10; ++i){

                for (int i = 0; i < matr_sz; ++i)
                    c[i] = 0;
                
                if (n_threads != 1){
                    #pragma omp parallel num_threads(n_threads)
                    {
                
                        int nthreads = n_threads;
                        int threadid = omp_get_thread_num();
                        int items_per_thread = matr_sz / nthreads;
                        int lb = threadid * items_per_thread;
                        int ub = (threadid == nthreads - 1) ? (matr_sz - 1) : (lb + items_per_thread - 1);
                
                        for (int i = lb; i < ub; ++i){
                            v[i] = i;
                            for (int j = 0; j < matr_sz; ++j){
                                a[i * matr_sz + j] = i + j;
                            }
                        }
                    } 
                    start_time = Start_Clock();
                    matrix_vector_product_omp(a.get(), v.get(), c.get(), matr_sz, matr_sz, n_threads);
                    time_of_exec = Stop_Clock() - start_time;
                }
                else{
                    for (int i = 0; i < matr_sz; ++i){
                        v[i] = i;
                        c[i] = 0;
                        for (int j = 0; j < matr_sz; ++j){
                            a[i * matr_sz + j] = i + j;
                        }
                    }
                    start_time = Start_Clock();
                    matrix_vector_product(a.get(), v.get(), c.get(), matr_sz, matr_sz);
                    one_thread_time = Stop_Clock() - start_time;

                    if (matr_sz == 20000)
                        result_one_thread_time_sz_20000 += one_thread_time;
                    else
                        result_one_thread_time_sz_40000 += one_thread_time;

                    time_of_exec = one_thread_time;
                }
                result_time += time_of_exec;
            }
            result_time /= 10;

            if (n_threads == 1 && matr_sz == 20000){
                result_one_thread_time_sz_20000 /= 10;
            }
            else if (n_threads == 1 && matr_sz == 40000){
                result_one_thread_time_sz_40000 /= 10;
            }

            // End of counting time


            if (matr_sz == 20000)
                file_vec_matr_mult_20000 << n_threads << ";" << result_time << ";" << result_one_thread_time_sz_20000/result_time << std::endl;
            else
                file_vec_matr_mult_40000 << n_threads << ";" << result_time << ";" << result_one_thread_time_sz_40000/result_time << std::endl;


        }
    }

    // end of first part

    // Second part - integral

    double one_thread_integral;
    double result_one_thread_integral = 0;

    for (int n_threads : Num_Threads){

        result_time = 0;

        for (int i = 0; i < 10; ++i){
            if (n_threads == 1){
                start_time = Start_Clock();
                integrate(a, b, nsteps);
                one_thread_integral = Stop_Clock() - start_time;
                result_one_thread_integral += one_thread_integral;
                time_of_exec = one_thread_integral;
                result_time += time_of_exec;
            }
            else{
                start_time = Start_Clock();
                integrate_omp(func, a, b, nsteps, n_threads);
                time_of_exec = Stop_Clock() - start_time;
                result_time += time_of_exec;
            }
        }

        result_time /= 10;

        if (n_threads == 1){
            result_one_thread_integral /= 10;
        }

        file_integr_40000000 << n_threads << ";" << result_time << ";" << result_one_thread_integral/result_time << std::endl;


    }

    closeFiles();   // close
                    // res_mult_20000.csv
                    // res_mult_40000.csv
                    // res_integr_40000000.csv
}

