#include "../model/coin.h"

void Coin::action(Mario &mario) {
    srand (time(NULL));

    int probability =  (rand() % 100) + 1;

    if (probability > 50) { 
        // falta el print
        mario.add_coin(1);
    }
}
