#include "../model/game_master.h"

void* fight_simulation(void * ptr){}
// cuando se muere un pokemon, un pront por ahora
void faint_pokemon(pokemon_t * pokemon){}

// cuando un entrenador intercambia pokemon
// un print por ahora
void switch_pokemon(player_t * player){}



// son solo prints que indiquen quien gano o perdio
void victory(player_t * player){}

void defeat(player_t * player){}

int set_efectivity(){}


// ojo, se llama 2 veces, 1 por jugador
// es solo create, no voy a inicializar valores
private_data_t * private_data_create(player_t * player){
    private_data_t * private_data = NULL;
    if(player->pokemon_team){ private_data = (private_data_t *) malloc(sizeof(private_data) * (TOTAL_POKEMON * 2));}
    return private_data;
}

battle_arena_t * battle_arena_create(){
    battle_arena_t * battle_arena = (battle_arena_t *) malloc(sizeof(battle_arena_t));
    sem_t * sem_array = (sem_t *)malloc(sizeof(sem_t) * (TOTAL_POKEMON * 2));
    if(!(battle_arena && sem_array)){
        fprintf(stderr, "error: could not allocate memory in battle arena creation.\n");
    }

    // inicializacion de lo de sincronizacion
    battle_arena->pokemon_semaphore_array = sem_array;
    for(size_t i = 0; i < (TOTAL_POKEMON * 2); i++){
        sem_init(&battle_arena->pokemon_semaphore_array[i], 0, 0);
    }

    // la barrera
    pthread_barrier_init(&battle_arena->barrier, NULL ,TOTAL_POKEMON * 2);

    return battle_arena;
}
