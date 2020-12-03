#include "../model/coin.h"


Coin::Coin() {
    this->element_type = COIN;
}

int Coin::action(Mario &mario) {
    int status = ELEMENT_IGNORED_BY_MARIO;
    
    // srand (time(NULL));
    Rand_Gen random;
    int probability =  random.get_rand_double();

    if (probability > 50) { 
        // falta el print
        mario.add_coin(1);
        status = ELEMENT_KILLED_BY_MARIO;
    }
    
    return status;
}
