#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void* nullFunction(void * args){
    return NULL;
}


// Para pedir argumentos de terminal
// no sea wevon y no los vuelva a hacer por input
int main(int argc, char* arg[]){

    struct timespec before, after;

    time_t fastestS;

    long fastestNs;

    size_t test_count = 0;

    if(argc == 1){
        test_count = 1;
    }else{
        test_count = (size_t)strtoul(arg[1], NULL, 10);
    }
    
    // malloc no inicializa las variables, calloc si
    // malloc tiene 1 argumento, calloc no
    // malloc que veo, free que sapeo
    pthread_t* threads = malloc((size_t)(test_count * sizeof(pthread_t)));
    

    // se empieza a medir el tiempo
    clock_gettime(CLOCK_MONOTONIC, &before);
    for (size_t i = 0; i < test_count; ++i) {
        clock_gettime(CLOCK_MONOTONIC, &before);
        pthread_create(&threads[i], NULL, nullFunction, NULL);
        clock_gettime(CLOCK_MONOTONIC, &after);
            if(i == 0){
                fastestS = after.tv_sec - before.tv_sec;
                fastestNs = after.tv_nsec - before.tv_nsec;
            }else{
                if(fastestS + fastestNs > (after.tv_sec - before.tv_sec) + (after.tv_nsec - before.tv_nsec)){
                    fastestS = after.tv_sec - before.tv_sec;
                    fastestNs = after.tv_nsec - before.tv_nsec;
                }
            }
    }

    for (size_t i = 0; i < test_count; ++i) {
        pthread_join(threads[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &after);


    printf("Minimum thread creation and destruction time was %ld.%lds among %zd tests\n", fastestS, fastestNs, test_count);
    printf("Amount of tests : %zd\n", test_count);
    free(threads);
    return 0;
}