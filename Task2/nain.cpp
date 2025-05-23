#include "func_lib/integr.h"
#include "func_lib/mult_matr_vec.h"
#include "time_lib/control_time.h"
#include "work_with_file_lib/file_manage.h"
#include <memory>

// for integral
const double a = -4.0;
const double b = 4.0;
const int nsteps = 40000000;
const double PI = 3.14159265358979323846;
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
                            c[i] = 0;
                            for (int j = lb; j < ub; ++j){
                                a[i * matr_sz + j] = i + j;
                            }
                        }
                    } 
                    Start_Clock();
                    matrix_vector_product_omp(a.get(), v.get(), c.get(), matr_sz, matr_sz, n_threads);
                    time_of_exec = Check_Clock();
                }
                else{
                    for (int i = 0; i < matr_sz; ++i){
                        v[i] = i;
                        c[i] = 0;
                        for (int j = 0; j < matr_sz; ++j){
                            a[i * matr_sz + j] = i + j;
                        }
                    }
                    Start_Clock();
                    matrix_vector_product(a.get(), v.get(), c.get(), matr_sz, matr_sz);
                    one_thread_time = Check_Clock();

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
                Start_Clock();
                integrate(a, b, nsteps);
                one_thread_integral = Check_Clock();
                result_one_thread_integral += one_thread_integral;
                time_of_exec = one_thread_integral;
                result_time += time_of_exec;
            }
            else{
                Start_Clock();
                integrate_omp(func, a, b, nsteps, n_threads);
                time_of_exec = Check_Clock();
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

