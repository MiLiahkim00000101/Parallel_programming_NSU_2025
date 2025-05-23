#include "mult_matr_vec.h"

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