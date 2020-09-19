#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

// Va a actuar de memoria compartida
typedef struct{
    
    size_t num_customers;
    size_t num_waiting_room;

    pthread_mutex_t mutex;
    sem_t customer_semaphore;
    sem_t barber_semaphore;

}barber_shop_t; 

typedef struct{

    size_t customer_id;
    barber_shop_t* barber_shop;

}customer_t;



// Metodos propios para el cliente
int customer_arrives(size_t id);
int customer_leaves(size_t id);
int customer_leaves_full(size_t id);
int get_hair_cut();

// Metodos propios para el barbero
int cut_hair();
int barber_leaves();

// otros metodos
void random_sleep(useconds_t min_milliseconds, useconds_t max_milliseconds);


int main(int argc, char* arg[]) {

	srand( time(NULL) );
    size_t num_customers = 0;

    if (argc >= 2) {
        num_customers = (size_t)strtoul(arg[1], NULL, 10);
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }


    return 0;
}

int customer_arrives(size_t id){
    printf("Customer number %zd has arrived\n", id);
    return 1;
}


int customer_leaves_full(size_t id){
    printf("Barbershop is full\n");
    printf("Customer number %zd is leaving\n", id);
    return 1;
}


int customer_leaves(size_t id){
    printf("Customer number %zd is leaving\n", id);
    return 1;
}


void random_sleep(useconds_t min_milliseconds, useconds_t max_milliseconds){
	useconds_t duration = min_milliseconds;
	useconds_t range = max_milliseconds - min_milliseconds;
	if ( range > 0 )
		duration += rand() % range;
	usleep( 1000 * duration );
}