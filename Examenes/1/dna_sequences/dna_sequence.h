#ifndef DNA_SEQUENCE_H
#define DNA_SEQUENCE_H

#define DNA_SEQUENCE_1 "abcdefgh"
#define DNA_SEQUENCE_2 "zxdeffrsafdsagfsgsrtg"

#include <pthread.h>

// van a haber 2 dna_sequence, uno por cada hilo de adn
typedef struct dna_sequence
{    
    // sale mas barato tener 2 arreglos que 3 estructuras
    int ocurrence_array_1 ['z' - 'a'];
    int ocurrence_array_2 ['z' - 'a'];
    // Este tiene que venir definido desde el main,
    // es variable compartida
    // desde el main se puede referenciar       
    int common_array['z' - 'a'];

    // numero de hilos en TOTAl
    size_t thread_amount;
    
    pthread_rwlock_t rwlock_dna_1;
    pthread_rwlock_t rwlock_dna_2;
    pthread_rwlock_t rwlock_common;
}dna_sequence_t;

dna_sequence_t * create_dna_sequence(size_t thread_amount);
int destroy_dna_sequence(dna_sequence_t * shared_data);

#endif