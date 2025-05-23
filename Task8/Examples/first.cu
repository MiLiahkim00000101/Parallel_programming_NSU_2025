#include "cuda_runtime.h"
#include <stdio.h>

__global__ void HelloWorld()
{
    printf("Hello world, %d, %d\n", blockIdx.x, threadIdx.x); 
}

int main(){

    HelloWorld <<< 2, 5 >>>(); // Первое число -- количество блоков, Второе -- количество потоков

    cudaDeviceSynchronize();

    return 0;
}