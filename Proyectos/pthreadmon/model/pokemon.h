#ifndef POKEMON_H
#define POKEMON_H

#include "../model/mapper.h"
#include "stdio.h"
#include "stdlib.h"


typedef struct
{
    //int id; // va aqui porque el usuario lo define
    int hp; // va aqui porque es dinamica
    pokemon_info_t * pokemon_info;
    move_info_t * fast_move_info;
    move_info_t * charged_move_info;
    type_info_t * type_info;

}pokemon_t;

pokemon_t * create_pokemon(int id);

#endif