#include "omp.h"
#include <stdio.h>

int main(){

    omp_set_num_threads(10);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("hello %d \n", id);
    }

}