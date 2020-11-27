#ifndef MARIO_H
#define MARIO_H

#include <bits/stdc++.h>

#define R "random"
#define L_COIN "less_coins"
#define M_COIN "most_coins"
#define A "attacker"

class Mario {
    public:
        Mario();
        Mario(std::string);
        bool is_active();
        void add_coin(int);
        void set_inactive();
    
    private:
        std::string attack_strategy;
        // amount of coins
        int coins;
        // bool to know if mario is active or not
        bool active;
        // mpi rank, needs to be implemented
        int my_id;
};

#endif