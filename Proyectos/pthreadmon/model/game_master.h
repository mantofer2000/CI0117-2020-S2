#ifndef MAPPER_H
#define MAPPER_H

#include "../model/player.h"
#include "pthread.h"
#include "semaphore.h"

// por orden y la vara se va a usar shared_data y private_data
// para las estructuras

typedef struct{
    pthread_barrier_t barrier;
    
    player_t * player_one;
    player_t * player_two;

}battle_arena_t;


// 1 hilo por pokemon
typedef struct{
    int thread_id;
    int trainer_id; // id dentro del equipo
    pokemon_t * pokemon;
    battle_arena_t * shared_data;
}private_data_t;

// el metodo parello
// ver opcion de nombres
void* fight_simulation(void * ptr);
// cuando se muere un pokemon, un pront por ahora
void faint_pokemon(pokemon_t * pokemon);

// cuando un entrenador intercambia pokemon
// un print por ahora
void switch_pokemon(player_t * player);



// son solo prints que indiquen quien gano o perdio
void victory(player_t * player);

void defeat(player_t * player);

int set_efectivity();


// los nombres de jugadores van a venir de parametros
// ya que hay que considerar que viene desde el GUI
private_data_t * private_data_create();

battle_arena_t * battle_arena_create();

#endif