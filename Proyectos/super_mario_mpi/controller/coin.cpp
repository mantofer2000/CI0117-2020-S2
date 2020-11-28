#include "../model/coin.h"


Coin::Coin() {
    this->element_type = COIN;
}

int Coin::action(Mario &mario) {
    int status = ELEMENT_IGNORED_BY_MARIO;
    
    // srand (time(NULL));

    int probability =  (rand() % 100) + 1;

    if (probability > 50) { 
        // falta el print
        mario.add_coin(1);
        status = ELEMENT_KILLED_BY_MARIO;
        // remember rank_id if
        std::cout << "Mario jumped and grabbed a coin! ";
    }
    // remember rank_id if
    std::cout << "Mario didn't jump and ingored the coin! ";
    
    return status;
}
