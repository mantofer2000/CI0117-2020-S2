#include <dna_sequence.h>

// primer parametro *2 es thread amount
dna_sequence_t * create_dna_sequence(size_t thread_amount){
    
    pthread_rwlock_t * rwlock_common = calloc(ARRAY_SIZE, sizeof(pthread_rwlock_t));
    pthread_rwlock_t * rwlock_dna_1 = calloc(ARRAY_SIZE, sizeof(pthread_rwlock_t));
    pthread_rwlock_t * rwlock_dna_2 = calloc(ARRAY_SIZE, sizeof(pthread_rwlock_t));
 
    for(size_t i = 0; i < thread_amount; i++){
        pthread_rwlock_init(&rwlock_common[i], NULL);
        pthread_rwlock_init(&rwlock_dna_1[i], NULL);
        pthread_rwlock_init(&rwlock_dna_2[i], NULL);
    }
    
    dna_sequence_t * shared_data = calloc(1, sizeof(dna_sequence_t));
    
    pthread_barrier_init(&shared_data->barrier, NULL, thread_amount);

    shared_data->rwlock_common = rwlock_common;
    shared_data->rwlock_dna_1 = rwlock_dna_1;
    shared_data->rwlock_dna_2 = rwlock_dna_2;

    // vea a ver si se necesita un for para hacer los arreglos en 0
    
    return shared_data;
}

int destroy_dna_sequence(dna_sequence_t * shared_data){
    size_t thread_amount = shared_data->thread_amount;    
    for(size_t i = 0; i < thread_amount; i++){
        pthread_rwlock_destroy(&shared_data->rwlock_common[i]);
        pthread_rwlock_destroy(&shared_data->rwlock_dna_1[i]);
        pthread_rwlock_destroy(&shared_data->rwlock_dna_2[i]);
    }
    pthread_barrier_destroy(&shared_data->barrier);
    free(shared_data);
    return 1;
}