#ifndef DNA_SEQUENCE_H
#define DNA_SEQUENCE_H

#define DNA_SEQUENCE_1 "abckh"
#define DNA_SEQUENCE_2 "llpqrsh"
#define ARRAY_SIZE 26

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// van a haber 2 dna_sequence, uno por cada hilo de adn
typedef struct dna_sequence
{    
    // sale mas barato tener 2 arreglos que 3 estructuras
    int ocurrence_array_1 [ARRAY_SIZE];
    int ocurrence_array_2 [ARRAY_SIZE];
    // Este tiene que venir definido desde el main,
    // es variable compartida
    // desde el main se puede referenciar       
    int common_array[ARRAY_SIZE];

    // numero de hilos en TOTAl
    size_t thread_amount;
    
    // son arrays
    pthread_barrier_t barrier;
    pthread_rwlock_t * rwlock_common;
    pthread_rwlock_t * rwlock_dna_1;
    pthread_rwlock_t * rwlock_dna_2;

}dna_sequence_t;

dna_sequence_t * create_dna_sequence(size_t thread_amount);
int destroy_dna_sequence(dna_sequence_t * shared_data);

#endif