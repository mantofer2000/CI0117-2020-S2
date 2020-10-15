#ifndef POKEMON_H
#define POKEMON_H

#include "../model/mapper.h"
#include "stdio.h"
#include "stdlib.h"

#define POKEMON_HP 1500


typedef struct
{
    //int id; // va aqui porque el usuario lo define
    int hp; // es 1500
    pokemon_info_t * pokemon_info;
    move_info_t * fast_move_info;
    move_info_t * charged_move_info;
    type_info_t * type_info;

}pokemon_t;

pokemon_t * pokemon_create(int id);
void pokemon_destroy(pokemon_t * pokemon);
void print(pokemon_t * );

#endif