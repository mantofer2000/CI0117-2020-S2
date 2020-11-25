#include "../model/hole.h"

void Hole::action(Mario &mario) {
    srand (time(NULL));

    int probability =  (rand() % 100) + 1;

    if (probability > 95) { 
        // falta el print
        mario.set_inactive();
    }
}