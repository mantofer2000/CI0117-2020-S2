#include "../model/player.h"

player_t* player_create(char* name)
{
    player_t* player = calloc(1, sizeof(player_t));
    player->pokemon_availible = TOTAL_POKEMON;
    player->player_name = name;

    return player;
}

void player_destroy(player_t* player)
{
    free(player->pokemon_team);
    free(player);
}

pokemon_t** choose_team(int id1, int id2, int id3)
{
    pokemon_t** pokemon_team = malloc( 3 * sizeof(pokemon_t*) );

    pokemon_team[0] = pokemon_create(id1);
    pokemon_team[1] = pokemon_create(id2);
    pokemon_team[2] = pokemon_create(id3);

    return pokemon_team;
}