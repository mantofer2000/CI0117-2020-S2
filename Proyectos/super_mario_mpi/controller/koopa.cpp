#include "../model/koopa.h"


Koopa_Troopa::Koopa_Troopa() {
    this->element_type = KOOPA_TROOPA;
}

int Koopa_Troopa::action(Mario &mario) {
    int status = ELEMENT_IGNORED_BY_MARIO;
    
    // srand (time(NULL));

    
    int probability = rand() % 100 + 1;


    if (probability > 0 && probability <= 10) {
        mario.set_inactive();
        status = ELEMENT_KILLED_MARIO;
    } else {
        if (probability > 10 && probability <= 63) {
            // mario salta y pasa
        } else {
            if (probability > 63 && probability <= 100) {
                // mario salta y mata al enemigo
                status = ELEMENT_KILLED_BY_MARIO;
            }
        }
    }
    return status;
}