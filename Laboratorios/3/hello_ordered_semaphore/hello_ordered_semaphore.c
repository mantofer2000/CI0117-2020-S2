#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    size_t message;
    size_t thread_count;
    
    size_t chose_thread;
    
    size_t next_thread;
    
    sem_t * sem_array;
} shared_message_t;

typedef struct {
    size_t thread_num;
    shared_message_t* shared_message;
    

} thread_data_t;


void* helloWorld(void* args) {

    thread_data_t* data = (thread_data_t*) args;

    size_t thread_num = data->thread_num;
    shared_message_t* shared_message = data->shared_message;


    if(thread_num == shared_message->chose_thread)
        shared_message->message++;
    
    printf("Hello world from thread number # %zu. The message is: %zu\n", thread_num, shared_message->message);
    
    ++shared_message->next_thread;
    
    if(shared_message->next_thread < shared_message->thread_count){
        sem_post(&shared_message->sem_array[shared_message->next_thread]);
    }


    return NULL;
}


int main(int argc, char* arg[]) {

    // arg[0] = command
    // arg[1] = first param

    struct timespec before, after;

    time_t fastestS;
    long fastestNs;
    clock_gettime(CLOCK_MONOTONIC, &before);
    
    size_t thread_count = 0;
    size_t chosen_thread = 0;

    if (argc >= 3) {
        thread_count = (size_t)strtoul(arg[1], NULL, 10);
        chosen_thread = (size_t)strtoul(arg[2], NULL, 10);

        if (chosen_thread < 0 || chosen_thread >= thread_count) {
            fprintf(stderr, "Error, invalid parameters\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }

    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));
    
    //pthread_mutex_t * mutex_array = (pthread_mutex_t*) malloc(thread_count * sizeof(pthread_mutex_t));
    
    sem_t * sem_array = (sem_t *)malloc(thread_count * sizeof(sem_t));



    shared_message_t* shared_message = (shared_message_t*)calloc(1, sizeof(shared_message_t));

    shared_message->message = 2020;
    shared_message->next_thread = 0;
    shared_message->sem_array = sem_array;
    shared_message->thread_count = thread_count;
    shared_message->chose_thread = chosen_thread;

    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));

    clock_gettime(CLOCK_MONOTONIC, &before);
    for (size_t i = 0; i < thread_count; ++i){
        //pthread_mutex_init(&shared_message->mutex_array[i], NULL);
        //pthread_mutex_lock(&shared_message->mutex_array[i]);

        sem_init(&shared_message->sem_array[i], 0, 0);
        thread_data_list[i].thread_num = i;
        thread_data_list[i].shared_message = shared_message;
        pthread_create(&threads[i], NULL, helloWorld, (void*)&thread_data_list[i]);
    }

    sem_post(&shared_message->sem_array[0]);

    for (size_t i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    for (size_t i = 0; i < thread_count; ++i) {
        sem_destroy(&shared_message->sem_array[i]);
    }

    printf("Hello world from main thread\n");
    clock_gettime(CLOCK_MONOTONIC, &after);

    free(threads);
    free(shared_message->sem_array);
    free(shared_message);
    free(thread_data_list);

    fastestS = after.tv_sec - before.tv_sec;
    fastestNs = after.tv_nsec - before.tv_nsec;
    printf("Execution time was %ld.%lds among %zd threads\n", fastestS, fastestNs, thread_count);

    return 0;
}