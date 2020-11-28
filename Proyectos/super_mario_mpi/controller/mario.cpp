#include "../model/mario.h"

Mario::Mario(std::string attack_strategy) {
    this->coins = 0;
    this->active = true;
    this->attack_strategy = attack_strategy;
}



Mario::Mario() {
    this->coins = 0;
    this->active = true;

    srand (time(NULL));

    int probability =  (rand() % 4) + 1;

    switch (probability) {
        case 1:
            this->attack_strategy = RANDOM_STRG;
            break;
        
        case 2:
            this->attack_strategy = L_COIN_STRG;
            break;
        
        case 3:
            this->attack_strategy = M_COIN_STRG;
            break;
        
        case 4:
            this->attack_strategy = ATTACKER_STRG;
            break;

        default:
            this->attack_strategy = RANDOM_STRG;
    }
}

void Mario::add_coin(int amount) {
    this->coins += amount; 
}

int Mario::get_coins_amount() {
    return this->coins;
}

bool Mario::is_active() {
    return this->active;
}

void Mario::set_inactive() {
    this->active = false;
}