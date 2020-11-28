#include "../model/hole.h"


Hole::Hole() {
    this->element_type = HOLE;
}

int Hole::action(Mario &mario) {
    int status = ELEMENT_IGNORED_BY_MARIO;
    
    // srand (time(NULL));

    int probability =  (rand() % 100) + 1;

    if (probability > 95) { 
        // falta el print
        mario.set_inactive();
        status = ELEMENT_KILLED_MARIO;
        // remember rank_id if
        std::cout << "Mario didn't jump the hole and had a brutal death! ";
    } else {
        // remember rank_id if
        std::cout << "Mario jumped and passed the hole! ";
    }
    
    return status;
}