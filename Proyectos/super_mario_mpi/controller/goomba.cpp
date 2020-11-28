#include "../model/goomba.h"

Little_Goomba::Little_Goomba() {
    this->element_type = LITTLE_GOOMBA;
}



int Little_Goomba::action(Mario &mario) {
    int status = ELEMENT_IGNORED_BY_MARIO;
    // srand (time(NULL));

    int probability =  (rand() % 100) + 1;

    if (probability > 0 && probability <= 5) { 
        // falta el print
        mario.set_inactive();
        status = ELEMENT_KILLED_MARIO;
        // remember rank_id if
        std::cout << "Mario didn't jump and was killed by a little goomba! ";
    } else {
        if (probability > 5 && probability <= 60) {
            // mario salta y pasa
            // no tiene efecto
            // remember rank_id if
            std::cout << "Mario jumped and passed a little goomba! ";
        } else {
            if (probability > 60 && probability <= 100) {
                // mario salta y mata al enemigo
                status = ELEMENT_KILLED_BY_MARIO;
                // remember rank_id if
                std::cout << "Mario jumped and killed a little goomba! ";
            }
        }
    }
    return status;
}