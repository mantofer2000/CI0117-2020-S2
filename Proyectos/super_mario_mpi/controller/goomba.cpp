#include "../model/goomba.h"

Little_Goomba::Little_Goomba() {
    this->element_type = LITTLE_GOOMBA;
}



int Little_Goomba::action(Mario &mario) {
    int status = ELEMENT_IGNORED_BY_MARIO;
    // srand (time(NULL));

     int probability = rand() % 100 + 1;

    if (probability > 0 && probability <= 5) { 
        mario.set_inactive();
        status = ELEMENT_KILLED_MARIO;
    } else {
        if (probability > 5 && probability <= 60) {
            // mario salta y pasa
            // no tiene efecto
        } else {
            if (probability > 60 && probability <= 100) {
                // mario salta y mata al enemigo
                status = ELEMENT_KILLED_BY_MARIO;
            }
        }
    }
    return status;
}