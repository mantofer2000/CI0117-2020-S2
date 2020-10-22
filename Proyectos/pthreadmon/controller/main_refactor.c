
// main tonto por ahora
#include "../model/game_master2.h"

int is_an_option(pokemon_t** options, int id)
{
    for ( int index = 0; index < 5; ++index )
        if ( options[index]->pokemon_info->id == id )
            return 1;

    return 0;
}

void choose_pokemon(player_t* player, pokemon_t** options)
{
    int id1, id2, id3;
    do
    {
        printf("Choose three of the above:\n");
        scanf("%d %d %d", &id1, &id2, &id3);
    }
    while (!(is_an_option(options, id1)) || !(is_an_option(options, id2))
            || !(is_an_option(options, id3)));

    player->pokemon_team = choose_team(id1, id2, id3);
}

pokemon_t** generate_random_pokes()
{
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
    return random_pokemon;
}

// El main esta en pthreadmon_ui.c para ir probando la interfaz
int main(){
    srand(time(NULL));
    // poner el initialize de mapper.c
    initialize_data();
    
    // hay que corregir donde va esta vara
    // recordar hacer el main lo menos cargado posible

    player_t * player_one = player_create("Marco");
    
    printf("Options for %s:\n", player_one->player_name);
    pokemon_t** random_pokemon = generate_random_pokes();
    
    choose_pokemon(player_one, random_pokemon);

    player_t* player_two = player_create("Gabriel");

    printf("Options for %s:\n", player_two->player_name);
    random_pokemon = generate_random_pokes();

    choose_pokemon(player_two, random_pokemon);

    initialize_fight(player_one, player_two);



    //destroy_pokemon(my_pokemon);
    

    return 0;
}