#include "../model/goomba.h"

void Little_Goomba::action(Mario &mario) {
    srand (time(NULL));

    int probability =  (rand() % 100) + 1;

    if (probability > 0 && probability <= 5) { 
        // falta el print
        mario.set_inactive();
    } else {
        if (probability > 5 && probability <= 60) {
            // mario salta y pasa
            // no tiene efecto
        } else {
            if (probability > 60 && probability <= 100) {
                // mario salta y mata al enemigo
            }
        }
    }
}