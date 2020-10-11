#ifndef ATTACK_H
#define ATTACK_H

#include "../model/type.h"
#include <time.h>
#include <sys/types.h>

typedef struct attack{
    int id;
    char* name;
    useconds_t cooldown;
    int energy; //cantidad acumulada
    int energy_gain; //cantidad que gana, revisar los nombres
    type_t * type;
}attack_t;

#endif