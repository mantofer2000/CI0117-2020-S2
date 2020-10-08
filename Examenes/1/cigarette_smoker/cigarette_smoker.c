#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>


//sem_t semaforos[3]; // vector de 3 semaforos uno por fumador
sem_t agente;


/*
Variables modificadas y creadas por marco para el examen
*/

pthread_t mutex;
pthread_cond_t cond_var[3];

size_t materiales[3];
#define PAPEL 0
#define TABACO 1
#define CERILLO 2

typedef void *(*smokers_t)(void *);


 // El fumador cero tiene papel infinito.
void* fumador_0(void* arg)
{
	while (true)
	{
		nanosleep((struct timespec[]){{0, rand() % 3000000000}}, NULL); // Sleep para visualizar de mejor manera los threads
		printf("El fumador cero tiene papel y esta esperando para fumar.\n");

		pthread_mutex_lock(&mutex);
		if(!(materiales[TABACO] != 0 && materiales[CERILLO] != 0)){
			pthread_cond_wait(&cond_var[PAPEL], &mutex);
		}
		pthread_mutex_unlock(&mutex);
		
		printf("El fumador cero recibio tabaco y cerillos. Ahora esta fumando.\n");
		sleep(1);
		sem_post(&agente);// Activa el semáforo del agente para que proceda a poner los siguientes ingredientes.
	}

	return NULL;
}


 
//El fumador uno tiene cerillos infinitos.
void* fumador_1(void* arg)
{
	while (true)
	{
		nanosleep((struct timespec[]){{0, rand() % 30000000000}}, NULL);
		printf("El fumador uno tiene cerillos y esta esperando para fumar.\n");

		
		pthread_mutex_lock(&mutex);
		if(!(materiales[PAPEL] != 0 && materiales[TABACO] != 0)){
			pthread_cond_wait(&cond_var[CERILLO], &mutex);
		}
		pthread_mutex_unlock(&mutex);

		printf("El fumador uno recibio tabaco y papel. Ahora esta fumando.\n");
		sleep(1);
		sem_post(&agente);
	}

	return NULL;
}

//El fumador dos tiene tacabo infinito.
void* fumador_2(void* arg)
{
	while (true)
	{
		nanosleep((struct timespec[]){{0, rand() % 3000000000}}, NULL);
		printf("El fumador dos tiene tabaco y esta esperando para fumar.\n");

		pthread_mutex_lock(&mutex);
		if(!(materiales[PAPEL] != 0 && materiales[CERILLO] != 0)){
			pthread_cond_wait(&cond_var[TABACO], &mutex);
		}
		pthread_mutex_unlock(&mutex);

		//sem_wait(&semaforos[2]);
		printf("El fumador dos recibio cerillos y papel. Ahora esta fumando.\n");
		sleep(1);
		sem_post(&agente);
	}

	return NULL;
}


int main(int argc, char* arvg[])
{
	srand(time(NULL));
	sem_init(&agente, 0, 1); // semaforo del agente.
	pthread_t fumadores[3];// vector de threads
	smokers_t metodos_fumadores[3] = { fumador_0, fumador_1, fumador_2 };// Metodos para los threads.

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_var[0], NULL);
	pthread_cond_init(&cond_var[1], NULL);
	pthread_cond_init(&cond_var[2], NULL);


	for (int i = 0; i < 3; ++i) // Aqui se inicializa el semaforo de cada fumador *thread* y se crea cada thread con su respectiva funcion.
	{
		//sem_init(&semaforos[i], 0, 0);
		if(pthread_create(&fumadores[i], NULL, metodos_fumadores[i], NULL) == EAGAIN)
		{
			perror("Recursos insuficientes, no se han creado los hilos\n");
			return 0;
		}
	}


	sleep(3);
	while (true) // aca el agente va a empeza a distribuir 2 ingredientes en cada iteracion, solo un thread podra tomarlos para evitar deadlocks.
	{
	
		
		sem_wait(&agente);// espera para que que el fumador que este fumando termine de fumar y el pueda poner  los materiales de nuevo.
		for(size_t i = 0; i < 3; i++){
			materiales[i] = 0;
		}

		int ready = 0;
		while(ready < 2){
			int random = rand() % 3;
			if(materiales[random] == 0){
				materiales[random] = 1;
				ready++;
			}
		}
		if(materiales[PAPEL] == 0){
			pthread_cond_signal(&cond_var[PAPEL]);
		}else
		{
			if(materiales[CERILLO] == 0){
				pthread_cond_signal(&cond_var[CERILLO]);
			}else
			{
				pthread_cond_signal(&cond_var[TABACO]);
			}
			
		}
		
		
		//sem_post(&semaforos[rand() % 3]); // distribuye dos materiales para un solo fumador.
	}

	for (int i = 0; i < 3; ++i)
	{
		pthread_join(fumadores[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	sem_destroy(&agente);
	pthread_cond_destroy(&cond_var[0]);
	pthread_cond_destroy(&cond_var[1]);
	pthread_cond_destroy(&cond_var[2]);

}
