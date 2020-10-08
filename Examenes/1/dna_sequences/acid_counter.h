#ifndef BASE_COUNTER_H
#define BASE_COUNTER_H

#include "dna_sequence.h"

typedef struct acid_counter{
    // sale mas barato tener 2 arreglos que 3 estructuras
    size_t dna_id; // 1 o 2
    size_t thread_id;
    dna_sequence_t * shared_data;
}acid_counter_t;


acid_counter_t * create_acid_counter(size_t thread_amount, dna_sequence_t* shared_data);
int destroy_acid_counter(acid_counter_t *  private_data); 
void* process_dna(void* args);

#endif