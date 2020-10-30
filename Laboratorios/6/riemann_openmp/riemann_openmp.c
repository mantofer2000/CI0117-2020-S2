#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


typedef struct timespec walltime_t;

void walltime_start(walltime_t* start);
double walltime_elapsed(const walltime_t* start);
size_t set_thread_amount(size_t max_num_threads, size_t number_of_rectangles);

//private_data_t * set_private_data(size_t num_threads, double delta_x, double point_a, double point_b);

double calculate_area(int thread_count, double point_a, double point_b, double delta_x, size_t number_of_rectangles){
    double result = 0.0;
    //double jump = thread_count;

    double begin_rec = point_a;
    //double end_rec = point_a + delta_x;
    

    #pragma omp parallel for num_threads(thread_count) reduction(+: result)
    for(int i = 0; i < number_of_rectangles; i++){
        begin_rec = point_a + (delta_x * i);
        result += delta_x * ((begin_rec * begin_rec) + 1);
        
    }
    
    return result;
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
        return (void) fprintf(stderr, "Usage: riemann_omp point_a point_b number_of_rectangles number_of_threads\n"), 1;
    }
    double a = (double) point_a;
    double b = (double) point_b;
    double dou_number_of_rectangles = (double) number_of_rectangles;


    num_threads = set_thread_amount(max_num_threads, number_of_rectangles);
    //preguntar por esto y la clausula
    //omp_set_num_threads(set_thread_amount(max_num_threads, number_of_rectangles));
    double delta_x = (b - a) / dou_number_of_rectangles;
    
    
    walltime_t start;
    walltime_start(&start);

    area = calculate_area(num_threads, point_a, point_b, delta_x, number_of_rectangles);
    
    elapsed = walltime_elapsed(&start);

    printf("The area is: %lf\n", area);
    printf("Execution time: %lfs\n", elapsed);
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