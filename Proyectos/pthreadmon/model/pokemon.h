#ifndef POKEMON_H
#define POKEMON_H

#include "../model/mapper.h"

#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include <math.h>

#define POKEMON_HP 1500
#define BONUS 2.3
#define TRUE 1
#define FALSE 0

typedef struct
{
    int hp; // es 1500
    int efectivity; // por default es 1, pero depende del ambiente que puede cambiar
    int energy; // en la energia actual, cada vez que aterriza un ataque rapido la carga

    int is_attacking; // GABRIEL -> Para la interfaz
    int attacking_fast;
    int attacking_charged;
    
    pokemon_info_t * pokemon_info;
    move_info_t * fast_move_info;
    move_info_t * charged_move_info;
    type_info_t * type_info;

}pokemon_t;

pokemon_t * pokemon_create(int id);

int pokemon_fast_attack(pokemon_t * pokemon);
int pokemon_charged_attack(pokemon_t * pokemon);
int pokemon_charged_attack_availible(pokemon_t * pokemon);

int pokemon_availible(pokemon_t * pokemon);

void pokemon_destroy(pokemon_t * pokemon);
void print(pokemon_t * );

#endif