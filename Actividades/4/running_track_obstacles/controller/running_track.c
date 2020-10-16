#define _XOPEN_SOURCE 600

#include <stdlib.h>
#include "../model/running_track.h"

running_track_t* running_track_create() {
    running_track_t* running_track = calloc(1, sizeof(running_track_t));

    running_track->lanes_start_line = calloc(NUM_LANES, sizeof(int));
    running_track->lanes_finish_line = calloc(NUM_LANES, sizeof(int));

    running_track->position = 1;

    running_track->obstacles_matrix = calloc(NUM_LANES, sizeof(int*));
    for ( int row = 0; row < NUM_OBSTACLES; ++row )
        running_track->obstacles_matrix[row] = calloc(NUM_OBSTACLES, sizeof(int));

    pthread_mutex_init(&running_track->mutex_position, NULL);
    pthread_barrier_init(&running_track->barrier_start_line, NULL, NUM_LANES);

    return running_track;
}


void running_track_destroy(running_track_t* running_track) {

    pthread_mutex_destroy(&running_track->mutex_position);
    pthread_barrier_destroy(&running_track->barrier_start_line);

    for ( int row = 0; row < NUM_OBSTACLES; ++row )
        free(running_track->obstacles_matrix[row]);
    
    free(running_track->obstacles_matrix);

    free(running_track->lanes_start_line);
    free(running_track->lanes_finish_line);

    free(running_track);

}