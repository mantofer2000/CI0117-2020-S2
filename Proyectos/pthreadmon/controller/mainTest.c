
// main tonto por ahora
#include "../model/player.h"

// El main esta en pthreadmon_ui.c para ir probando la interfaz
int main(){
    // poner el initialize de mapper.c
    initialize_data();
    
    // hay que corregir donde va esta vara
    // recordar hacer el main lo menos cargado posible

    player_t * player_one = player_create("Marco");
    player_one->pokemon_team = choose_team();

    player_t * player_two = player_create("Gabriel");
    player_two->pokemon_team = choose_team();


    


    
    //destroy_pokemon(my_pokemon);
    

    return 0;
}