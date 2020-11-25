#include "../model/koopa.h"

void Koopa_Troopa::action(Mario &mario) {
    srand (time(NULL));

    int probability =  (rand() % 100) + 1;

    if (probability > 0 && probability <= 10) { 
        // falta el print
        mario.set_inactive();
    } else {
        if (probability > 10 && probability <= 63) {
            // mario salta y pasa
        } else {
            if (probability > 63 && probability <= 100) {
                // mario salta y mata al enemigo
            }
        }
    }
}