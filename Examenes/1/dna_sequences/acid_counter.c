#include "acid_counter.h"

// falta validacion
// asuntos de memoria
acid_counter_t * create_acid_counter(size_t thread_amount, dna_sequence_t* shared_data){
    acid_counter_t * ptr = calloc(thread_amount, sizeof(acid_counter_t));
    
    // revisar esta J, se me desmadra con modulo
    size_t j = 0;
    for(size_t i = 0; i < thread_amount; i++){
        
        ptr[i].thread_id = i;
        if(i <= (thread_amount/2 - 1 )){
            ptr[i].dna_id = 1;
            ptr[i].array_id = i;
        }else{
            ptr[i].dna_id = 2;
            ptr[i].array_id = j;
            j++;
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
    dna_sequence_t * shared_data = acid_counter->shared_data;
    
    
    size_t my_dna = acid_counter->dna_id;
    size_t my_thread_id = acid_counter->thread_id;
    size_t jump = shared_data->thread_amount/2;
    size_t big_jump = shared_data->thread_amount;
    size_t my_array = acid_counter->array_id;

    if(my_dna == 1){
        for(size_t i = my_thread_id; i < sizeof(DNA_SEQUENCE_1) - 1; i = i + jump){
            pthread_rwlock_wrlock(&shared_data->rwlock_dna_1[0]);
                shared_data->ocurrence_array_1[DNA_SEQUENCE_1[i] - 'a']++;
            pthread_rwlock_unlock(&shared_data->rwlock_dna_1[0]);   
        }    
    }else{
        for(size_t i = my_array; i < sizeof(DNA_SEQUENCE_2) - 1; i = i + jump){
            pthread_rwlock_wrlock(&shared_data->rwlock_dna_2[DNA_SEQUENCE_2[i] - 'a']);
                shared_data->ocurrence_array_2[DNA_SEQUENCE_2[i] - 'a']++;
            pthread_rwlock_unlock(&shared_data->rwlock_dna_2[DNA_SEQUENCE_2[i] - 'a']);
        }
    }


    // Inicio de la interseccion
    pthread_barrier_wait(&shared_data->barrier);
    for(size_t i = my_thread_id; i < ARRAY_SIZE; i = i + big_jump){
        pthread_rwlock_rdlock(&shared_data->rwlock_dna_1[i]);
        pthread_rwlock_rdlock(&shared_data->rwlock_dna_2[i]);
        if(shared_data->ocurrence_array_1[i] != 0 && shared_data->ocurrence_array_2[i] != 0){
            pthread_rwlock_wrlock(&shared_data->rwlock_common[i]);
                shared_data->common_array[i]++;
            pthread_rwlock_unlock(&shared_data->rwlock_common[i]);
        }
        pthread_rwlock_unlock(&shared_data->rwlock_dna_1[i]);
        pthread_rwlock_unlock(&shared_data->rwlock_dna_2[i]);
    }  

    return NULL;
}

