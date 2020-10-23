#ifndef GAME_MASTER_H
#define GAME_MASTER_H

#include "../model/player.h"


// este numero puede cambiar, recordadr interfaz
#define THREAD_NUM 6
#define TEAM_1 0
#define TEAM_2 1
#define PLAYER_AMOUNT 2

// mutex para la ui
pthread_mutex_t battle_arena_mutex;

// por orden y la vara se va a usar shared_data y private_data
// para las estructuras

typedef struct{
    pthread_barrier_t barrier;    
    int battle_over;
    sem_t * pokemon_semaphore_array;

    pthread_mutex_t mutex;
    pthread_cond_t cond_var;
    pthread_cond_t sleep_cond_var;

    player_t ** players_array;
    int gotta_wait;
    player_t * winner;
    
    pokemon_t ** poke_p_array;
}battle_arena_t;


// 1 hilo por pokemon
typedef struct{
    int thread_id;
    size_t team_number;
    size_t team_id; // id dentro del equipo
    pokemon_t * pokemon;
    battle_arena_t * shared_data;
}private_data_t;

// GABRIEL
battle_arena_t* battle_arena;

pokemon_t* active_poke_one;
pokemon_t* active_poke_two;

void initialize_fight(player_t * p_one, player_t * p_two);


void* fight_simulation(void * ptr);


int switch_pokemon(battle_arena_t * battle_arena, int team_id, int thread_id);

int is_battle_over(player_t * p_one, player_t * p_two);


// son solo prints que indiquen quien gano o perdio
//void victory(player_t * player);

//void defeat(player_t * player);

//int set_efectivity();

// los nombres de jugadores van a venir de parametros
// ya que hay que considerar que viene desde el GUI
// NO LOS INICILIZA, SOLO CREA, FALTA DESTROYS
//private_data_t * private_data_create(player_t *, player_t * );
//battle_arena_t * battle_arena_create();

#endif