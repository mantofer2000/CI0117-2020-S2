#ifndef MARIO_H
#define MARIO_H

#include <bits/stdc++.h>

#define RANDOM_STRG "random"
#define L_COIN_STRG "less_coins"
#define M_COIN_STRG "most_coins"
#define ATTACKER_STRG "attacker"

class Mario {
    public:
        Mario(int);
        //Mario(char);
        void add_coin(int);
        int get_coins_amount();
        bool is_active();
        void set_inactive();
        std::string get_attack_strategy();
        void set_attack_strategy(char);
    
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