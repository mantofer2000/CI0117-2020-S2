#ifndef MAPPER_H
#define MAPPER_H

#include "../model/player.h"


// este numero puede cambiar, recordadr interfaz
#define THREAD_NUM 6

// por orden y la vara se va a usar shared_data y private_data
// para las estructuras

typedef struct{
    pthread_barrier_t barrier;    
    int battle_over;
    sem_t * pokemon_semaphore_array;

    pthread_mutex_t mutex;
    pthread_cond_t cond_var;

    player_t * player_one;
    player_t * player_two;

    // estos pokemon son los que estan
    // peleando actualmente
    // estan aca ya que se puedan quitar la vida
    // entre si
    
    int poke_p_one_id;
    int poke_p_two_id;
    
    pokemon_t * poke_p_one;
    pokemon_t * poke_p_two;

}battle_arena_t;


// 1 hilo por pokemon
typedef struct{
    int thread_id;
    size_t trainer_id;
    size_t team_id; // id dentro del equipo
    pokemon_t * pokemon;
    battle_arena_t * shared_data;
}private_data_t;


void initialize_fight(player_t * p_one, player_t * p_two);

// el metodo parello
// ver opcion de nombres
void* fight_simulation(void * ptr);
// cuando se muere un pokemon, un pront por ahora
//void faint_pokemon(pokemon_t * pokemon);


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