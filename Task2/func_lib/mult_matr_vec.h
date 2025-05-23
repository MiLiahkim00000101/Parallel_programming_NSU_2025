#ifndef ____MULT_MATR_VEC____
#define ____MULT_MATR_VEC____

#include <omp.h>


void matrix_vector_product_omp(double *a, double *b, double *c, int m, int n, int n_threads); // Многопоточное умножение матрицы на вектор
void matrix_vector_product(double *a, double *b, double *c, int m, int n); // Однопоточное умножение матрицы на вектор


#endif