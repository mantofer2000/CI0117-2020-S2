#include "../model/game_master.h"
 #include <time.h>

void* fight_simulation(void * ptr){
    private_data_t * private_data = (private_data_t *) ptr;
    battle_arena_t * shared_data = (battle_arena_t*)private_data->shared_data;
    
    pthread_barrier_wait(&shared_data->barrier);
    
    if(private_data->team_id != 0){
        sem_wait(&shared_data->pokemon_semaphore_array[private_data->thread_id]);
    }

    if(!is_battle_over(shared_data->player_one, shared_data->player_two)){
        if(private_data->trainer_id == 1){
            shared_data->poke_p_one = private_data->pokemon;
        }else{
            shared_data->poke_p_two = private_data->pokemon;
            
        }
        pthread_mutex_lock(&shared_data->mutex);
            pthread_cond_signal(&shared_data->cond_var);
        pthread_mutex_unlock(&shared_data->mutex);

        printf(" READY TO FIGHT %d \n", private_data->thread_id);
    }

    // toda esta mierda se puede mejorar si se implemetnara un array de jugadores
    // en vez de dos punteros
    // si queda tiempo cambiar    
    //pthread_mutex_lock(&pokemon->shared_data->mutex);
    
    while(private_data->pokemon->hp > 0 && !(is_battle_over(shared_data->player_one, shared_data->player_two))){
        if(shared_data->gotta_wait == TRUE){
            pthread_mutex_lock(&shared_data->mutex);
                pthread_cond_wait(&shared_data->cond_var, &shared_data->mutex);
            pthread_mutex_unlock(&shared_data->mutex);
        }
        
        if(private_data->trainer_id == 1){            
            if(pokemon_charged_attack_availible(private_data->pokemon) == TRUE){
                private_data->pokemon->efectivity = get_efectivity(shared_data->poke_p_two->type_info->id, private_data->pokemon->charged_move_info->typeId);
                pthread_mutex_lock(&shared_data->mutex);
                    shared_data->gotta_wait = TRUE;
                pthread_mutex_unlock(&shared_data->mutex);
                shared_data->poke_p_two->hp -= pokemon_charged_attack(private_data->pokemon);
                pthread_mutex_lock(&shared_data->mutex);
                    shared_data->gotta_wait = FALSE;
                    pthread_cond_broadcast(&shared_data->sleep_cond_var);
                pthread_mutex_unlock(&shared_data->mutex);
                usleep(private_data->pokemon->charged_move_info->cooldown);    
            }else{
                private_data->pokemon->efectivity = get_efectivity(shared_data->poke_p_two->type_info->id, private_data->pokemon->fast_move_info->typeId);
                shared_data->poke_p_two->hp -= pokemon_fast_attack(private_data->pokemon);
                usleep(private_data->pokemon->fast_move_info->cooldown);
            }
            if(!shared_data->poke_p_two->hp){
                pthread_mutex_lock(&shared_data->mutex);
                    if(!is_battle_over(shared_data->player_one, shared_data->player_two)){
                            pthread_cond_wait(&shared_data->cond_var, &shared_data->mutex);
                    }
                pthread_mutex_unlock(&shared_data->mutex);
                    
            }
        }else{
            if(pokemon_charged_attack_availible(private_data->pokemon) == TRUE){
                private_data->pokemon->efectivity = get_efectivity(shared_data->poke_p_one->type_info->id, private_data->pokemon->charged_move_info->typeId);
                pthread_mutex_lock(&shared_data->mutex);
                    shared_data->gotta_wait = TRUE;
                pthread_mutex_unlock(&shared_data->mutex);


                shared_data->poke_p_one->hp -= pokemon_charged_attack(private_data->pokemon);
                
                pthread_mutex_lock(&shared_data->mutex);
                    shared_data->gotta_wait = FALSE;
                    pthread_cond_broadcast(&shared_data->sleep_cond_var);
                pthread_mutex_unlock(&shared_data->mutex);

                usleep(private_data->pokemon->charged_move_info->cooldown);

            }else{
                private_data->pokemon->efectivity = get_efectivity(shared_data->poke_p_one->type_info->id, private_data->pokemon->fast_move_info->typeId);
                shared_data->poke_p_one->hp -= pokemon_fast_attack(private_data->pokemon);
                usleep(private_data->pokemon->fast_move_info->cooldown);
            }
                if(!shared_data->poke_p_one->hp){   
                    pthread_mutex_lock(&shared_data->mutex);
                        if(!is_battle_over(shared_data->player_one, shared_data->player_two)){
                            pthread_cond_wait(&shared_data->cond_var, &shared_data->mutex);
                        }
                    pthread_mutex_unlock(&shared_data->mutex);
                    
                }
        }
    }

    if(private_data->pokemon->hp <= 0){
        if(private_data->trainer_id == 1){
            shared_data->player_one->pokemon_availible -= 1;
            //int to_wake = (switch_pokemon(shared_data, private_data->team_id, private_data->thread_id) *  2) + 1;
            printf("I LOST, %d , ENEMY HP : %d \n", private_data->thread_id, shared_data->poke_p_two->hp);
        }else{
            shared_data->player_two->pokemon_availible -= 1;
            //int to_wake = (switch_pokemon(shared_data, private_data->team_id, private_data->thread_id) *  2);
            printf("I LOST, %d, \n", private_data->thread_id);
        }
        
        if(!is_battle_over(shared_data->player_one, shared_data->player_two)){sem_post(&shared_data->pokemon_semaphore_array[private_data->thread_id + 2]);}
        
        
        if(is_battle_over(shared_data->player_one, shared_data->player_two)){
            for(size_t i = 0; i < TOTAL_POKEMON * 2; i++){
                sem_post(&shared_data->pokemon_semaphore_array[i]);
            }
            pthread_cond_broadcast(&shared_data->cond_var);
        }
    
    }
   return NULL;

}


// cuando se muere un pokemon, un pront por ahora
//void faint_pokemon(pokemon_t * pokemon){}

// cuando un entrenador intercambia pokemon
// un print por ahora


// son solo prints que indiquen quien gano o perdio
//void victory(player_t * player){}

//void defeat(player_t * player){}

int get_efectivity(int target_pokemon_type, int attacking_move_type){
    if (weaknesses_matrix[target_pokemon_type][attacking_move_type]) {
    return 1.6;
    } else if (resistances_matrix[target_pokemon_type][attacking_move_type]) {
        return 0.625;
    } else if (immunities_matrix[target_pokemon_type][attacking_move_type]) {
        return 0.390625;
    } else {// ninguno de los anteriores
    return 1;
}
}



void initialize_fight(player_t * p_one, player_t * p_two){
    battle_arena_t * battle_arena = (battle_arena_t *) malloc(sizeof(battle_arena_t));
    battle_arena->gotta_wait = FALSE;

    pthread_mutex_init(&battle_arena->mutex, NULL);
    pthread_barrier_init(&battle_arena->barrier, NULL, TOTAL_POKEMON * 2);
    pthread_cond_init(&battle_arena->cond_var, NULL);
    pthread_cond_init(&battle_arena->sleep_cond_var, NULL);

    sem_t * sem_array = (sem_t * ) malloc(sizeof(sem_t) * (TOTAL_POKEMON * 2));

    size_t h = 0;
    for(; h < TOTAL_POKEMON * 2; h++){
        sem_init(&sem_array[h], 0, 0);
    }

    battle_arena->pokemon_semaphore_array = sem_array;

    private_data_t * private_data_array = (private_data_t *) calloc((TOTAL_POKEMON * 2) , sizeof(private_data_t));
    pthread_t * threads = (pthread_t * ) malloc(THREAD_NUM * sizeof(pthread_t)); 




    /*INICIALIZACION SHARED DATA*/
    battle_arena->player_one = p_one;
    battle_arena->player_two = p_two;
    battle_arena->battle_over = is_battle_over(p_one, p_two);
    battle_arena->poke_p_one = p_one->pokemon_team[0];
    battle_arena->poke_p_two = p_two->pokemon_team[0];



    /*INICIALIZACION PRIVATE Y PTHREAD_CREATE*/
    /*NO SE ESTA TOMANDO EN CUENTA LA INTERFAZ*/
    int poke_id_one = 0;
    int poke_id_two = 0;

    size_t i = 0;
    /*CUANDO SE AGREGUE MAS HILOS QUE SEAN AL FINAL, POR EL ARRAY DE SEMAFOROS*/
    for(; i < (TOTAL_POKEMON * 2); i++){
        /*es del jugador 2*/
        if((int)(i % 2) == 0){
            private_data_array[i].thread_id = (int)i;
            private_data_array[i].trainer_id = 2;
            private_data_array[i].pokemon = p_two->pokemon_team[poke_id_two];
            private_data_array[i].team_id = poke_id_two;
            poke_id_two++;
            private_data_array[i].shared_data = battle_arena;
        }else{
            private_data_array[i].thread_id = i;
            private_data_array[i].trainer_id = 1;
            private_data_array[i].pokemon = p_one->pokemon_team[poke_id_one];
            private_data_array[i].team_id = poke_id_one;
            poke_id_one++;
            private_data_array[i].shared_data = battle_arena;
        }
    }

    size_t j = 0;
    for(; j < (TOTAL_POKEMON * 2); j++){
        pthread_create(&threads[j], NULL, fight_simulation, &private_data_array[j]);
    }

    size_t k = 0;
    for(; k < THREAD_NUM; k++){
        pthread_join(threads[k], NULL);
    }

    if(battle_arena->player_one->pokemon_availible == FALSE){
        battle_arena->winner = battle_arena->poke_p_two;
    }else{
        battle_arena->winner = battle_arena->poke_p_one;
    }

    size_t l = 0;
    for(; l < TOTAL_POKEMON * 2; l++){
        sem_destroy(&sem_array[l]);
    }

    pthread_mutex_destroy(&battle_arena->mutex);
    pthread_barrier_destroy(&battle_arena->barrier);
    pthread_cond_destroy(&battle_arena->cond_var);

    free(threads);
    free(private_data_array);
    free(battle_arena);

}

int is_battle_over(player_t * p_one, player_t * p_two){
    int is_over = (p_one->pokemon_availible && p_two->pokemon_availible) ? FALSE : TRUE;
    return is_over;
}