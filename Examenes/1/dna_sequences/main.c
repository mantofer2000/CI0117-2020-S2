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
        pthread_create(&threads[i], NULL, process_dna, NULL);
    }

    for(size_t i = 0; i < thread_amount; i++){
        pthread_join(threads[i], NULL);
    }

    destroy_dna_sequence(dna_sequence);
    destroy_acid_counter(acid_counter);

    return 0;
}