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

}barbershop_t; 

typedef struct{

    size_t customer_id;
    barbershop_t* barber_shop;

}customer_t;



// Metodos propios para el cliente
int customer_arrives(size_t id);
int customer_leaves(size_t id);
int customer_leaves_full(size_t id);
int get_haircut(size_t id);

// Metodos propios para el barbero
int cut_hair();
int barber_leaves();
int barber_wakes();
int barber_sleeps();

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

    // +1 por el barbero
    // Revisar porque hay que dar las validacion
    // Por si no c pueden almacenar memoria
    pthread_t* threads = malloc((size_t)((num_customers + 1) * sizeof(pthread_t)));
    barbershop_t* shared_barbershop = (barbershop_t*)calloc(1, sizeof(barbershop_t));



    free(threads);
    free(shared_barbershop);

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

int get_haircut(size_t id){
    printf("Customer %zd will get a haircut\n", id);
    return 1;
}

// metodos barbero
int cut_hair(){
    printf("Barber will give a haircut\n");
    random_sleep(1500, 3000);
    printf("The barber has finished with the haircut\n");
    return 1;
}

int barber_leaves(){
    printf("The barber has finished for today\n");
    return 1;    
}

int barber_sleeps(){
    printf("There are no customers \n");
    printf("The barber will go to sleep \n");
    return 1;
}


int barber_wakes(){
    printf("The barber is awake\n");
    return 1;
}

void random_sleep(useconds_t min_milliseconds, useconds_t max_milliseconds){
	useconds_t duration = min_milliseconds;
	useconds_t range = max_milliseconds - min_milliseconds;
	if ( range > 0 )
		duration += rand() % range;
	usleep( 1000 * duration );
}