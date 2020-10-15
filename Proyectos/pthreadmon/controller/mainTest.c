
// main tonto por ahora
#include "../model/pokemon.h"

int main(){
    // poner el initialize de mapper.c

    initialize_data();

    pokemon_t * my_pokemon = create_pokemon(5);
    printf("%s\n", my_pokemon->pokemon_info->speciesName);
    
    destroy_pokemon(my_pokemon);
    

    return 0;
}