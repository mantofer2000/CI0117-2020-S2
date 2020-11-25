#include "../model/mario.h"

Mario::Mario() {
    this->coins = 0;
    this->active = true;
}

void Mario::add_coin(int amount) {
    this->coins += amount; 
}

bool Mario::is_active() {
    return this->active;
}

void Mario::set_inactive() {
    this->active = false;
}