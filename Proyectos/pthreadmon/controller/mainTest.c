
// main tonto por ahora
#include "../model/game_master.h"

// El main esta en pthreadmon_ui.c para ir probando la interfaz
int main(){
    srand(time(NULL));
    // poner el initialize de mapper.c
    initialize_data();
    
    // hay que corregir donde va esta vara
    // recordar hacer el main lo menos cargado posible

    player_t * player_one = player_create("Marco", 0, 1, 2);

    int id1, id2, id3;
    pokemon_t** random_pokemon = malloc( 5 * sizeof(pokemon_t*) );

    int poke = 0;
    int rand_id = 0;
    int is_repeated = 0;
    while (poke < 5)
    {
        rand_id = (rand() % 49);
        
        for ( int index = 0; index < poke; ++index )
        {
            if ( poke > 0 )
            {
                if ( random_pokemon[index]->pokemon_info->id == rand_id )
                {
                    is_repeated = 1;
                    break;
                }
                else
                {
                    is_repeated = 0;
                }
            }
            
        }
        if ( !(is_repeated) )
        {
            random_pokemon[poke] = pokemon_create(rand_id);
            printf("%d: %s\n", random_pokemon[poke]->pokemon_info->id, random_pokemon[poke]->pokemon_info->speciesName); 
            ++poke;
        }
    }

    //for ( int poke = 0; poke < 5; ++poke )
    //    random_pokemon[poke] = pokemon_create(rand() % 56);

    printf("Escoja 3:\n");
    printf("First: ");
    scanf("%d", &id1);
    printf("Second: ");
    scanf("%d", &id2);
    printf("Third: ");
    scanf("%d", &id3);
    player_t * player_two = player_create("Gabriel", id1, id2, id3);

    initialize_fight(player_one, player_two);



    //destroy_pokemon(my_pokemon);
    

    return 0;
}