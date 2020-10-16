#define _XOPEN_SOURCE 600

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../model/runner.h"

void random_sleep(useconds_t min_milliseconds, useconds_t max_milliseconds)
{
	useconds_t duration = min_milliseconds;
	useconds_t range = max_milliseconds - min_milliseconds;
	if ( range > 0 )
		duration += rand() % range;
	usleep( 1000 * duration );
}

void fixed_sleep(useconds_t duration)
{
	usleep( 1000 * duration );
}

runner_t* runner_create(int id, int preparation_time, int running_time) {
    runner_t* runner = calloc(1, sizeof(runner_t));
    runner->id = id;
    runner->preparation_time = preparation_time;
    runner->running_time = running_time;
    runner->time_per_obstacle = (running_time / 5);

    return runner;
}

void runner_destroy(runner_t* runner) {
    free(runner);
}

void* run(void* args) {
    run_data_t* data = (run_data_t*) args;

    // Goes to the start line;
    fixed_sleep((useconds_t)data->runner->preparation_time);
    *data->lane_start = 1;

    printf("Tread %d: Ready!\n", data->runner->id);
    pthread_barrier_wait(data->barrier_start_line);

    printf("Tread %d: Go!!!\n", data->runner->id);
    // Running!! 
    //fixed_sleep((useconds_t)data->runner->running_time);

    for ( int obstacle = 0; obstacle < NUM_OBSTACLES; ++obstacle )
    {
        // El tiempo que duren en cada obstaculo.
        fixed_sleep((useconds_t)data->runner->time_per_obstacle);

        pthread_mutex_lock(data->mutex_position);

        data->obstacle_matrix[data->runner->id][obstacle] = 1;
        
        // Ya paso por el obstaculo anterior, volver a estaclecerlo en 0.
        if ( obstacle > 0 )
            data->obstacle_matrix[data->runner->id][obstacle - 1] = 0;

        pthread_mutex_unlock(data->mutex_position);
    }

    // Finish Line!
    pthread_mutex_lock(data->mutex_position);

    *data->lane_finish = *data->position;
    printf("Tread %d: Arrived at position %d\n", data->runner->id, *data->position);
    *data->position = *data->position + 1;

    pthread_mutex_unlock(data->mutex_position);

    fixed_sleep((useconds_t)1000);
}