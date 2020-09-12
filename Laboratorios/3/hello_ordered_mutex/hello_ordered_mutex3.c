#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t message;
    size_t thread_amount;
    size_t next_thread;
    pthread_mutex_t * mutex_array;

    //size_t chose_thread;
} shared_message_t;

typedef struct {
    size_t thread_num;
    shared_message_t* shared_message;
    
} thread_data_t;


void* helloWorld(void* args) {
    thread_data_t* data = (thread_data_t*) args;

    size_t thread_num = data->thread_num;
    shared_message_t* shared_message = data->shared_message;
    
    pthread_mutex_lock(&shared_message->mutex_array[thread_num]);


    // esto es espera activa, se queda en el while
    // consumiendo recursos hasta que le toque
    //while (thread_num != shared_message->next_thread);

    //printf("Hello world from thread number # %zu. The message is: %zu\n", thread_num, shared_message->message);
    printf("Hello world from thread number # %zu\n", thread_num);

    ++shared_message->next_thread;

    if(shared_message->next_thread <= shared_message->thread_amount){
        //pthread_mutex_unlock(&shared_message->mutex_array[shared_message->next_thread]);
    }

    return NULL;
}


int main(int argc, char* arg[]) {

    // arg[0] = command
    // arg[1] = first param

    size_t thread_count = 0;
    //size_t chosen_thread = 0;

    if (argc >= 2) {
        thread_count = (size_t)strtoul(arg[1], NULL, 10);
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }

    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));

    shared_message_t* shared_message = (shared_message_t*)calloc(1, sizeof(shared_message_t));
    shared_message->message = 2020;
    shared_message->mutex_array = malloc(thread_count * sizeof(pthread_mutex_t));
    shared_message->thread_amount = thread_count;
    shared_message->next_thread = 0;
    
    thread_data_t* thread_data_list = malloc(thread_count * sizeof(thread_data_t));


    for (size_t i = 0; i < thread_count; ++i) {
        pthread_mutex_init(&shared_message->mutex_array[i], NULL);
        
        thread_data_list[i].thread_num = i;
        thread_data_list[i].shared_message = shared_message;
        
        pthread_create(&threads[i], NULL, helloWorld, (void*)&thread_data_list[i]);
    }

    //pthread_mutex_unlock(&shared_message->mutex_array[0]);



    for (size_t i = 0; i < thread_count; ++i) {        
        pthread_join(threads[i], NULL);
    }

    for (size_t i = 0; i < thread_count; ++i) {        
        pthread_mutex_destroy(&shared_message->mutex_array[i]);
    }

    printf("Hello world from main thread\n");

    free(threads);
    free(shared_message->mutex_array);
    free(shared_message);
    free(thread_data_list);
    // revisar free() invalid pointer

    return 0;
}