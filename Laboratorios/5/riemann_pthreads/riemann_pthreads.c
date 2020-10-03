#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


typedef struct{
    pthread_mutex_t mutex;
    double result;
}shared_data_t;

typedef struct{
    size_t thread_id;
    size_t num_threads;

    double begin;
    double end;
    double delta_x;

    shared_data_t* shared_data;
}private_data_t;


typedef struct timespec walltime_t;

void walltime_start(walltime_t* start);
double walltime_elapsed(const walltime_t* start);
size_t set_thread_amount(size_t max_num_threads, size_t number_of_rectangles);
private_data_t * set_private_data(size_t num_threads, double delta_x, double point_a, double point_b);

void* calculate_area(void* args){
    private_data_t * private_data = (private_data_t*) args;
    shared_data_t * shared_data = (shared_data_t*)private_data->shared_data;

    double delta_x = private_data->delta_x;
    double result = 0.0;
    double jump = (double)private_data->num_threads;
    double begin = private_data->begin;
    double end = private_data->end;

    //f(x) = x^2 + 1

    for(double i = begin; i <= (end - delta_x); i += (delta_x * jump)){
        result += delta_x * ((i * i) + 1);
    }

    //printf("The area THREAD: %ld\n", jump);

    pthread_mutex_lock(&shared_data->mutex);
        shared_data->result += result;
    pthread_mutex_unlock(&shared_data->mutex);
    return NULL;
}

int main(int argc, char* argv[])
{
    size_t point_a, point_b, number_of_rectangles, max_num_threads, num_threads;
    double area, elapsed;


    // Ya esta en size_t, pero tambien revisar que no entren negativos
    if ( argc >= 4 )
    {
        point_a = strtoul(argv[1], NULL, 10);
        point_b = strtoul(argv[2], NULL, 10);
        
        if ( point_b <= point_a )
            return (void) fprintf(stderr, "Error! point_b must be higher than point_a\n"), 2;

        number_of_rectangles = strtoul(argv[3], NULL, 10);
        max_num_threads = strtoul(argv[4], NULL, 10);

        if(max_num_threads == 0)
            return (void) fprintf(stderr, "Error! Thread_num must not be 0\n"), 3;
    }
    else{
        return (void) fprintf(stderr, "Usage: riemann_pthreads point_a point_b number_of_rectangles\n"), 1;
    }
    double a = (double) point_a;
    double b = (double) point_b;
    double dou_number_of_rectangles = (double) number_of_rectangles;


    num_threads = set_thread_amount(max_num_threads, number_of_rectangles);
    double delta_x = (b - a) / dou_number_of_rectangles;
    
    
    private_data_t * private_data = set_private_data(num_threads, delta_x, a, b);
    shared_data_t * shared_data = (shared_data_t *)calloc(1, sizeof(shared_data_t));
    pthread_t* threads = (pthread_t*)malloc((num_threads) * sizeof(pthread_t));
    shared_data->result = 0;

    pthread_mutex_init(&shared_data->mutex, NULL);
    

    
    walltime_t start;
    walltime_start(&start);

    for(size_t i = 0; i < num_threads; i++){
        private_data[i].shared_data = shared_data;
        pthread_create(&threads[i],  NULL, calculate_area, (void*)&private_data[i]);

    }
    // area = calculate_area(point_a, point_b, number_of_rectangles);
    for(size_t it = 0; it < num_threads; it++){pthread_join(threads[it], NULL);}
    area = shared_data->result;
    
    
    elapsed = walltime_elapsed(&start);

    printf("The area is: %lf\n", area);
    printf("Execution time: %lfs\n", elapsed);
    pthread_mutex_destroy(&shared_data->mutex);
    free(private_data);
    free(shared_data);
    free(threads);
    return 0;
}

void walltime_start(walltime_t* start)
{
    clock_gettime(CLOCK_MONOTONIC, start);
}

double walltime_elapsed(const walltime_t* start){
    walltime_t finish;
    clock_gettime(CLOCK_MONOTONIC, &finish);

    double elapsed = (finish.tv_sec - start->tv_sec);
    elapsed += (finish.tv_nsec - start->tv_sec ) / 1000000000.0;

    return elapsed;
}

size_t set_thread_amount(size_t max_num_threads, size_t number_of_rectangles){
    size_t return_value = 0;
    
    if(max_num_threads == number_of_rectangles){
        return_value = max_num_threads;
    }
    if(max_num_threads > number_of_rectangles){
        return_value =  number_of_rectangles;
    }
    if(max_num_threads < number_of_rectangles){
        return_value =  max_num_threads;
    }
    return return_value;

}

private_data_t * set_private_data(size_t num_threads, double delta_x, double point_a, double point_b){
    private_data_t * private_data = (private_data_t * )calloc(num_threads, sizeof(private_data_t));
    for(int  i = 0; i < (int)num_threads; i++){
        private_data[i].thread_id = i + 1;
        private_data[i].begin = ( point_a) + (i * delta_x);
        private_data[i].end = point_b;
        private_data[i].delta_x = delta_x;
        private_data[i].num_threads = num_threads;
    }
    return private_data;
}
