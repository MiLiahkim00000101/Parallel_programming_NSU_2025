#ifndef ____INTEGR____
#define ____INTEGR____

double integrate(double a, double b, int n);
double integrate_omp(double (*func)(double), double a, double b, int n, int n_threads);
double func(double x);


#endif