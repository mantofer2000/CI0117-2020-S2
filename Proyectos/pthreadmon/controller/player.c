#include "../model/player.h"

player_t* player_create(char* name)
{
    player_t* player = calloc(1, sizeof(player_t));
    player->pokemon_availible = TOTAL_POKEMON;
    player->player_name = name;
    player->pokemon_team = choose_team();

    return player;
}

void player_destroy(player_t* player)
{
    free(player->pokemon_team);
    free(player);
}

pokemon_t** choose_team()
{
    pokemon_t** pokemon_team = malloc( 3 * sizeof(pokemon_t*) );

    // Estupidez por ahora para crear al equipo de pokemon
    for ( int id = 0; id < 3; ++id ){
        pokemon_team[id] = pokemon_create(id + 5);
    }
    return pokemon_team;
}