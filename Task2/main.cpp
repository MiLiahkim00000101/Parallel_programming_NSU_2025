#include <iostream>
#include <fstream>
#include <omp.h>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <memory>


int N = 1; // amount of threads default
int Matrix_Size = 20000; // matrix size

void matrix_vector_product_omp(double *a, double *b, double *c, int m, int n)
{
    #pragma omp parallel num_threads(N)
    {
        int nthreads = N;
        int threadid = omp_get_thread_num();
        int items_per_thread = m / nthreads;
        int lb = threadid * items_per_thread;
        int ub = (threadid == nthreads - 1) ? (m - 1) : (lb + items_per_thread - 1);

        for (int i = lb; i <= ub; ++i){
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
        for (int j = 0; j < n; ++j){
            c[i] += a[i * n + j] * b[j];
        }
    }
}

int main(int argc, char **argv){

    char execute_one_thread_prog = 1;
    char flag_parallel_init = 0;
    char flag_append = 0;


    // Обработаем аргументы командной строки
    std::ofstream out_file;
    int rez = 0;
	while ( (rez = getopt(argc, argv, "hamN:s:i")) != -1){
		switch (rez) {
            case 'a':
                flag_append = 1;
                break;
            case 'm':
            {
                out_file.open("results.txt");
                out_file << "Amount_of_threads;Time_of_execution;Speedup" << std::endl;
                break;
            }
            case 'N':
                N = std::stoi(optarg); break;
            case 's':
                Matrix_Size = std::stoi(optarg);
                break;
                
            case 'h':
                printf("Parameters:\n\t-a\t--- append file\n\t-m\t--- make(create) file\
                \n-N\t--- Number of threads to use. Example <-N16> using 16 threads.\
                \n\t-s\t--- matrix Size. Example <-s40000> using size 40000 for matrix.\
                \n\t-q\t--- Quick execution don't execute One thread programm(if q program uses pre-defined \
value of time of multiplying vector on matrix else it's count it)");
                return 0;
            case 'i':
                flag_parallel_init = 1; break;
            case '?':
                printf("Error found !\n");
                return 0;
            default: 
                out_file.open("results.txt", std::ios::app);    
        }

	}



    if (flag_append){
        out_file.open("results.txt", std::ios::app); 
    }


    int T;
    int S;
    std::chrono::duration<double> one_thread_time{0};
    std::chrono::duration<double> multi_thread_time{0};



    std::unique_ptr<double []> a{std::make_unique<double[]>(Matrix_Size * Matrix_Size)},
     v{std::make_unique<double[]>(Matrix_Size)}, c{std::make_unique<double[]>(Matrix_Size)};


    if (flag_parallel_init){
        #pragma omp parallel num_threads(N)
        {
    
            int nthreads = N;
            int threadid = omp_get_thread_num();
            int items_per_thread = Matrix_Size / nthreads;
            int lb = threadid * items_per_thread;
            int ub = (threadid == nthreads - 1) ? (Matrix_Size - 1) : (lb + items_per_thread - 1);
    
            for (int i = lb; i < ub; ++i){
                v[i] = i;
                c[i] = 0;
                for (int j = lb; j < ub; ++j){
                    a[i * Matrix_Size + j] = i + j;
                }
            }
        } 
    }
    else{
        for (int i = 0; i < Matrix_Size; ++i){
            v[i] = i;
            c[i] = 0;
            for (int j = 0; j < Matrix_Size; ++j){
                a[i * Matrix_Size + j] = i + j;
            }
        }
    }
    
    

    for (int i = 0; i < 10; ++i){
        const auto start_single{std::chrono::steady_clock::now()};

        matrix_vector_product(a.get(), v.get(), c.get(), Matrix_Size, Matrix_Size);

        const auto end_single{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds_single{end_single - start_single};
        one_thread_time += elapsed_seconds_single;
    }
    

    for (int i = 0; i < 10; ++i){
        const auto start_multi{std::chrono::steady_clock::now()};

        matrix_vector_product_omp(a.get(), v.get(), c.get(), Matrix_Size, Matrix_Size);

        const auto end_multi{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds_multi{end_multi - start_multi};
        multi_thread_time += elapsed_seconds_multi;
    }

    one_thread_time /= 10;

    multi_thread_time /= 10;

    
    std::cout << N << std::endl;

    

    out_file << N << ";" << multi_thread_time.count() << ";" << one_thread_time.count()/multi_thread_time.count() << std::endl;

    return 0;
}