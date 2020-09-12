#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t message;
    size_t thread_amount;
    size_t next_thread;

    pthread_mutex_t * mutex_array;
} shared_data_t;

typedef struct {
    size_t thread_num;
    shared_data_t* shared_data;
} private_data_t;


void* hello_world(void* ptr){  
    private_data_t* thread_data = (private_data_t*) ptr;

    size_t thread_num = thread_data->thread_num;
    shared_data_t* shared_data = thread_data->shared_data;
    
    pthread_mutex_lock(&shared_data->mutex_array[thread_num]);
    


    //printf("Hello world from thread number # %zu. The message is: %zu\n", thread_num, shared_message->message);
    printf("Hello world from thread number # %zu\n", thread_num);



    if(shared_data->next_thread < shared_data->thread_amount){
        shared_data->next_thread = shared_data->next_thread + 1;
        pthread_mutex_unlock(&shared_data->mutex_array[shared_data->next_thread]);
    }

    return NULL;
}

shared_data_t * init_shared_data(size_t message, size_t thread_amount){
    shared_data_t * shared_data = calloc(1, sizeof(shared_data_t));
    shared_data->message = message;
    shared_data->thread_amount = thread_amount;
    shared_data->next_thread = 0;

    // cuidado con esto

    shared_data->mutex_array = malloc(thread_amount * sizeof(pthread_mutex_t));


    return shared_data;
}


int main(int argc, char* arg[]){
    // arg[0] = command
    // arg[1] = first param

    size_t thread_count = 0;

    if (argc >= 2) {
        thread_count = (size_t)strtoul(arg[1], NULL, 10);
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }

    shared_data_t * shared_data = init_shared_data(2020, thread_count);
    private_data_t* private_data = malloc(thread_count * sizeof(private_data_t));

    pthread_t* threads = malloc((thread_count * sizeof(pthread_t)));

    for(size_t i = 0; i < thread_count; i++){
        pthread_mutex_init(&shared_data->mutex_array[i], NULL);
        private_data[i].thread_num = i;
        private_data[i].shared_data = shared_data;

        pthread_create(&threads[i], NULL, hello_world, (void*)&private_data[i]);   
    }

    pthread_mutex_unlock(&shared_data->mutex_array[0]);

    for (size_t i = 0; i < thread_count; ++i) {        
        pthread_join(threads[i], NULL);
    }

    for (size_t i = 0; i < thread_count; ++i) {        
        pthread_mutex_destroy(&shared_data->mutex_array[i]);
    }

    printf("Hello world from main thread\n");


    free(threads);
    free(shared_data->mutex_array);
    free(shared_data);
    free(private_data);
    return 0;
}