#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    //size_t message;
    //size_t next_thread;
    
    
    pthread_mutex_t mutex;
    size_t thread_count;
    size_t position;



} shared_data_t;

typedef struct {
    size_t thread_num;
    shared_data_t* shared_data;

} thread_data_t;


void* race(void* args) {

    thread_data_t* data = (thread_data_t*) args;

    size_t thread_num = data->thread_num;
    
    shared_data_t* shared_data = data->shared_data;

    size_t thread_count = shared_data->thread_count;


   
	pthread_mutex_lock(&shared_data->mutex);
	
	shared_data->position++;

	printf("Thread %zu / %zu: I arrived at position %zu\n",thread_num, thread_count,shared_data->position);
	
	pthread_mutex_unlock(&shared_data->mutex);
    
   
    
    return NULL;
}


int main(int argc, char* arg[]) {

    // falta ver errores cuando los malloc y calloc no sirve
    // pruebe valgrind

    size_t thread_count = 0;

    if (argc >= 2) {
        thread_count = (size_t)strtoul(arg[1], NULL, 10);
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }

    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));

    shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));

    //shared_data->message = 2020;
    //shared_data->next_thread = 0;


    pthread_mutex_init(&shared_data->mutex, NULL);



    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));

    for (size_t i = 0; i < thread_count; ++i) {
        thread_data_list[i].thread_num = i;
        thread_data_list[i].shared_data = shared_data;
        pthread_create(&threads[i], NULL, race, (void*)&thread_data_list[i]);
    }

    for (size_t i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }


   
    pthread_mutex_destroy(&shared_data->mutex);
    free(threads);
    free(shared_data);
    free(thread_data_list);

    return 0;
}