#include "../model/hole.h"


Hole::Hole() {
    this->element_type = HOLE;
}

int Hole::action(Mario &mario) {
    int status = ELEMENT_IGNORED_BY_MARIO;
    
    // srand (time(NULL));

    Rand_Gen random;
    int probability =  random.get_rand_double();


    if (probability > 95) { 
        // falta el print
        mario.set_inactive();
        status = ELEMENT_KILLED_MARIO;
    }
    
    return status;
}