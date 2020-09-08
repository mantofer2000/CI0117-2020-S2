#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t message;


    size_t thread_amount;

    //size_t chose_thread;
    //size_t next_thread;
} shared_message_t;

typedef struct {
    size_t thread_num;
    shared_message_t* shared_message;

    // se pide que cada hilo tenga 1 mutex, preguntar esta madre


    pthread_mutex_t lock;
    pthread_mutex_t next_lock;

} thread_data_t;


void* helloWorld(void* args) {

    thread_data_t* data = (thread_data_t*) args;

    size_t thread_num = data->thread_num;
    shared_message_t* shared_message = data->shared_message;

    // esto es espera activa, se queda en el while
    // consumiendo recursos hasta que le toque

    //while (thread_num != shared_message->next_thread);

    //if (thread_num == shared_message->chose_thread) {
        shared_message->message = 2021;
   // }

    printf("Hello world from thread number # %zu. The message is: %zu\n", thread_num, shared_message->message);
    
    //++shared_message->next_thread;
    
    return NULL;
}


int main(int argc, char* arg[]) {

    // arg[0] = command
    // arg[1] = first param

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

    shared_message_t* shared_message = (shared_message_t*)calloc(1, sizeof(shared_message_t));

    shared_message->message = 2020;
    //shared_message->chose_thread = chosen_thread;
    //shared_message->next_thread = 0;

    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));

    /*
        {
            thread_num: 0,
            shared_message: {}
        },
        {
            thread_num: 1,
            shared_message: {}
        },
    */

    for (size_t i = 0; i < thread_count; ++i) {
        thread_data_list[i].thread_num = i;
        thread_data_list[i].shared_message = shared_message;
        
        if(i != 0){
            pthread_mutex_init(&thread_data_list[i].lock, NULL);
            // init y destroy
            // lock y unlock
        }
        pthread_create(&threads[i], NULL, helloWorld, (void*)&thread_data_list[i]);
        
    }

    for (size_t i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Hello world from main thread\n");

    free(threads);
    free(shared_message);
    free(thread_data_list);

    return 0;
}