#include <iostream>
#include <fstream>
#include <omp.h>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <memory>
#include <cmath>


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
        int nthreads = omp_get_num_threads();
        int threadid = omp_get_thread_num();
        int items_per_thread = n / nthreads;
        int lb = threadid * items_per_thread;
        int ub = (threadid == nthreads - 1) ? (n - 1) : (lb + items_per_thread - 1);

        double sumlock = 0;

        for (int i = lb; i <= ub; i++)
            sumlock += func(a + h * (i + 0.5));

        #pragma omp atomic
        sum += sumlock;
            
    }
    
    sum *= h;
    
    
    return sum;
}