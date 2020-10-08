#include "acid_counter.h"

// falta validacion
// asuntos de memoria
acid_counter_t * create_acid_counter(size_t thread_amount, dna_sequence_t* shared_data){
    acid_counter_t * ptr = calloc(thread_amount, sizeof(acid_counter_t));
    for(size_t i = 0; i < thread_amount; i++){
        ptr[i].thread_id = i;
        if(i < thread_amount/2){
            ptr[i].dna_id = 1;
        }else{
            ptr[i].dna_id = 2;
        }
        ptr[i].shared_data = shared_data;
    }
    return ptr; 
}

int destroy_acid_counter(acid_counter_t *  private_data){
    free(private_data);
    return 1;
}

// falta implementarlo
// metodo paralelo
void* process_dna(void* args){
    acid_counter_t * acid_counter = (acid_counter_t *)args;
    
    
    
    return NULL;
}

