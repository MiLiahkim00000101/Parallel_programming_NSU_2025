#include <stdio.h>
#include <omp.h>
#include <time.h>


int main(int argc, char **argv){
    #pragma omp parallel num_threads(6)       /* <--- Fork */
    {
        printf("Hello, multithreaded world: thread %d of %d\n",
                omp_get_thread_num(), omp_get_num_threads());

        /* Sleep for 30 seconds */
         nanosleep(&(struct timespec){.tv_sec = 30}, NULL);

    }                           /* <--- Barrier & join */

    

}