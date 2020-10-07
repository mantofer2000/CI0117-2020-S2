#ifndef DNA_SEQUENCE_H
#define DNA_SEQUENCE_H

#define SEQUENCE_1 abcdefgh
#define SEQUENCE_2 zxdeffrsafdsagfsgsrtg

#include <pthread.h>

// van a haber 2 dna_sequence, uno por cada hilo de adn
typedef struct dna_sequence
{
    // sale mas barato tener 2 arreglos que 3 estructuras
    int ocurrence_array_1 ['z' - 'a'];
    int ocurrence_array_2 ['z' - 'a'];
    // Este tiene que venir definido desde el main,
    // es variable compartida
    int common_array['z' - 'a'];
    // numero de hilos en TOTAl
    size_t thread_amount;
    pthread_barrier_t barrier;
    pthread_rwlock_t rwlock;
}dna_sequence_t;
#endif