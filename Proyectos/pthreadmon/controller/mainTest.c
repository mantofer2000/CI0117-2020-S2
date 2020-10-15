
// main tonto por ahora
#include "../model/pokemon.h"
#include "../model/player.h"


int main(){
    // poner el initialize de mapper.c
    initialize_data();
    // hay que corregir donde va esta vara
    // recordar hacer el main lo menos cargado posible

    player_t * player_one = create_pokemon("Marco");
    player_one->pokemon_team = choose_team();

    player_t * player_two = create_pokemon("Gabriel");
    player_two->pokemon_team = choose_team();


    


    
    destroy_pokemon(my_pokemon);
    

    return 0;
}