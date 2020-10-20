#ifndef PLAYER_H
#define PLAYER_H

#define TOTAL_POKEMON 3

#include "../model/pokemon.h"

typedef struct player
{
    char* player_name;
    //int player_num;
    int pokemon_availible;
    pokemon_t** pokemon_team; // Es un puntero a punteros porque cada pokemon es un puntero

} player_t;

player_t* player_create(char* player_name);
void player_destroy(player_t* player);

pokemon_t** choose_team(int id1, int id2, int id3);

#endif 