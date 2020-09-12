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
    shared_data_t* shared_message;
} private_data_t;


void* hello_world(void* ptr){

}

shared_data_t * init_shared_data(size_t message, size_t thread_amount){
    shared_data_t * shared_data = calloc(1, sizeof(shared_data_t));
    shared_data->message = message;
    shared_data->thread_amount = thread_amount;
    shared_data->next_thread = 1;
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

    free(shared_data);

    return 0;
}