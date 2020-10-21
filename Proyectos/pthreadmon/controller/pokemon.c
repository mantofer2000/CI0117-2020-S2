#include "../model/pokemon.h"

// aqui ya viene en supuesto que el id esta correcto
pokemon_t * pokemon_create(int id){
    pokemon_t * new_pokemon = (pokemon_t *) malloc(sizeof(pokemon_t));
    new_pokemon->pokemon_info =  (pokemon_info_t *) malloc(sizeof(pokemon_info_t));
    new_pokemon->fast_move_info = (move_info_t *) malloc(sizeof(move_info_t));
    new_pokemon->charged_move_info = (move_info_t *) malloc(sizeof(move_info_t));
    new_pokemon->type_info = (type_info_t *) malloc(sizeof(type_info_t));

    if(!(new_pokemon->pokemon_info && new_pokemon->fast_move_info && new_pokemon->charged_move_info &&new_pokemon->type_info))
        fprintf(stderr, "error: could not allocate memory in pokemon creation.\n");
     
    //new_pokemon->id = id;
    // hay que cambiarlo
    new_pokemon->hp = POKEMON_HP;
    new_pokemon->efectivity = 1;
    new_pokemon->energy = 0;
    
    new_pokemon->pokemon_info->id = id;
    new_pokemon->pokemon_info->speciesName = get_pokemon_species_name(id);
    new_pokemon->pokemon_info->fastMoveId = get_pokemon_fast_move_id(id);
    new_pokemon->pokemon_info->chargedMoveId = get_pokemon_charged_move_id(id);
    new_pokemon->pokemon_info->typeId = get_pokemon_type_id(id);

    new_pokemon->fast_move_info->id = new_pokemon->pokemon_info->fastMoveId;
    new_pokemon->fast_move_info->cooldown = get_move_cooldown(new_pokemon->fast_move_info->id);
    new_pokemon->fast_move_info->moveName = get_move_name(new_pokemon->fast_move_info->id);
    new_pokemon->fast_move_info->energy = get_move_energy(new_pokemon->fast_move_info->id);
    new_pokemon->fast_move_info->energyGain = get_move_energy_gain(new_pokemon->fast_move_info->id);
    new_pokemon->fast_move_info->power = get_move_power(new_pokemon->fast_move_info->id);
    new_pokemon->fast_move_info->typeId = get_move_type_id(new_pokemon->fast_move_info->id);

    new_pokemon->charged_move_info->id = new_pokemon->pokemon_info->chargedMoveId;
    new_pokemon->charged_move_info->cooldown = get_move_cooldown(new_pokemon->charged_move_info->id);
    new_pokemon->charged_move_info->moveName = get_move_name(new_pokemon->charged_move_info->id);
    new_pokemon->charged_move_info->energy = get_move_energy(new_pokemon->charged_move_info->id);
    new_pokemon->charged_move_info->energyGain = get_move_energy_gain(new_pokemon->charged_move_info->id);
    new_pokemon->charged_move_info->power = get_move_power(new_pokemon->charged_move_info->id);
    new_pokemon->charged_move_info->typeId = get_move_type_id(new_pokemon->charged_move_info->id);

    new_pokemon->type_info->id = new_pokemon->pokemon_info->typeId;
    new_pokemon->type_info->typeName = get_type_name(new_pokemon->type_info->id);

    return new_pokemon;
}



void pokemon_destroy(pokemon_t * pokemon){
    
    free(pokemon->pokemon_info);
    free(pokemon->fast_move_info);
    free(pokemon->charged_move_info);
    free(pokemon->type_info);

    // liberando el puntero
    free(pokemon);
}



int pokemon_fast_attack(pokemon_t * pokemon){
    int damage = floor((pokemon->fast_move_info->power) * pokemon->efectivity * BONUS) + 1;
    pokemon->energy += pokemon->fast_move_info->energyGain;
    return damage;
}

int pokemon_charged_attack(pokemon_t * pokemon){
    int damage = floor((pokemon->charged_move_info->power) * pokemon->efectivity * BONUS) + 1;
    // REVISAR
    pokemon->energy = 0;
    return damage;
    
}

int pokemon_charged_attack_availible(pokemon_t * pokemon){
    int can_attack = FALSE;
    if(pokemon->energy >= pokemon->charged_move_info->energy){
        can_attack = TRUE;
    }
    return can_attack;
}

int pokemon_availible(pokemon_t * pokemon){
    int availible = (pokemon->hp) ? TRUE : FALSE; 
}