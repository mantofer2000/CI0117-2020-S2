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

    double begin;
    double end;
    double delta_x;

    shared_data_t* shared_data;
}private_data_t;


typedef struct timespec walltime_t;

void walltime_start(walltime_t* start);
double walltime_elapsed(const walltime_t* start);
double calculate_area(size_t point_a, size_t point_b, size_t number_of_rectangles);
size_t set_thread_amount(size_t max_num_threads, size_t number_of_rectangles);
private_data_t * set_private_data(size_t num_threads, double delta_x, size_t point_a, size_t point_b);

int main(int argc, char* argv[])
{
    size_t point_a;
    size_t point_b;
    size_t number_of_rectangles;
    // Esta la ingresa el usuario, pero puede que se tenga que reducir
    size_t max_num_threads;
    size_t num_threads;
    double area;
    double elapsed;


    // Ya esta en size_t, pero tambien revisar que no entren negativos
    if ( argc >= 4 )
    {
        point_a = strtoul(argv[1], NULL, 10);
        point_b = strtoul(argv[2], NULL, 10);
        if ( point_b < point_a )
        {
            return (void) fprintf(stderr, "Error! point_b must be higher than point_a\n"), 2;
        }
        number_of_rectangles = strtoul(argv[3], NULL, 10);
        max_num_threads = strtoul(argv[4], NULL, 10);
    }
    else{
        return (void) fprintf(stderr, "Usage: riemann_pthreads point_a point_b number_of_rectangles\n"), 1;
    }

    num_threads = set_thread_amount(max_num_threads, number_of_rectangles);
    double delta_x = ((double) point_b - (double) point_a) / number_of_rectangles;
    private_data_t * private_data = set_private_data(num_threads, delta_x, point_a, point_b);
    shared_data_t * shared_data = (shared_data_t *)calloc(1, sizeof(shared_data_t));
    
    pthread_mutex_init(&shared_data->mutex);
     

    
    walltime_t start;
    walltime_start(&start);
    area = calculate_area(point_a, point_b, number_of_rectangles);
    elapsed = walltime_elapsed(&start);

    printf("The area is: %lf\n", area);
    printf("Execution time: %lfs\n", elapsed);

    pthread_mutex_destroy(&shared_data->mutex);
    free(private_data);
    free(shared_data);


    return 0;
}

double calculate_area(size_t point_a, size_t point_b, size_t number_of_rectangles)
{
    double delta_x = ((double) point_b - (double) point_a) / number_of_rectangles;
    double result = 0.0;

    //f(x) = x^2 + 1
    for(double i = point_a; i < point_b; i = i + delta_x){
        result += delta_x * ((i * i) + 1);
    }
    return result;
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
    if(max_num_threads == number_of_rectangles){
        return max_num_threads;
    }
    if(max_num_threads > number_of_rectangles){
        return number_of_rectangles;
    }
    if(max_num_threads < number_of_rectangles){
        return max_num_threads;
    }
}

private_data_t * set_private_data(size_t num_threads, double delta_x, size_t point_a, size_t point_b){
    private_data_t * private_data = (private_data_t * )calloc(num_threads, sizeof(private_data_t));
    for(size_t i = 0; i < num_threads; i++){
        private_data[i].thread_id = i;
        private_data[i].begin = ((double) point_a) + (i * delta_x);
        private_data[i].end = (double) point_b;
        private_data[i].delta_x = delta_x;
    }
    return private_data;
}
