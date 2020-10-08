#define _XOPEN_SOURCE 600
#include "acid_counter.h"


int main(int argc, char* argv[]){
    // Numero de hilos
    size_t thread_amount;
    
    if (argc >= 1) {
        thread_amount = (size_t)strtoul(argv[1], NULL, 10);
    }else{
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }

    thread_amount = thread_amount * 2;

    dna_sequence_t * dna_sequence = create_dna_sequence(thread_amount);
    acid_counter_t * acid_counter = create_acid_counter(thread_amount, dna_sequence);

    pthread_t * threads = calloc(thread_amount, sizeof(pthread_t));


    for(size_t i = 0; i < thread_amount; i++){
        pthread_create(&threads[i], NULL, process_dna, &acid_counter[i]);
    }

    for(size_t i = 0; i < thread_amount; i++){
        pthread_join(threads[i], NULL);
    }

    char letter;
    
    printf("Sequence 1: Ocurrences: ");
    for(size_t i = 0; i < ARRAY_SIZE; i++){
        if(dna_sequence->ocurrence_array_1[i]!= 0){
            letter = 'a' + i;
            printf("%c = %d, ",  letter,  dna_sequence->ocurrence_array_1[i]);
        }
    }
    printf("\n");
    printf("Sequence 2: Ocurrences: ");
    for(size_t i = 0; i < ARRAY_SIZE; i++){
        if(dna_sequence->ocurrence_array_2[i]!= 0){
            letter = 'a' + i;
            printf("%c = %d, ",  letter, dna_sequence->ocurrence_array_2[i] );
        }
    }
    printf("\n");
    printf("Common Letters: ");

    for(size_t i = 0; i < ARRAY_SIZE; i++){
        if(dna_sequence->common_array[i]!= 0){
            letter = 'a' + i;
            printf("%c, ", letter);
        }
    }
    printf("\n");
    free(threads);
    
    //destroy_acid_counter(acid_counter);
    //destroy_dna_sequence(dna_sequence);
    // me daba error si llamaba a los metodos
    for(size_t i = 0; i < thread_amount; i++){
        pthread_rwlock_destroy(&dna_sequence->rwlock_common[i]);
        pthread_rwlock_destroy(&dna_sequence->rwlock_dna_1[i]);
        pthread_rwlock_destroy(&dna_sequence->rwlock_dna_2[i]);
    }
    pthread_barrier_destroy(&dna_sequence->barrier);
    free(dna_sequence->rwlock_common);
    free(dna_sequence->rwlock_dna_1);
    free(dna_sequence->rwlock_dna_2);   
    free(acid_counter);
    free(dna_sequence);

    return 0;
}