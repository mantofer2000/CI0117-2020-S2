#ifndef MARIO_H
#define MARIO_H

#include <bits/stdc++.h>


class Mario {
    public:
        Mario();
        bool is_active();
        void add_coin(int);
        void set_inactive();
    
    private:
        // amount of coins
        int coins;
        // bool to know if mario is active or not
        bool active;
        // mpi rank, needs to be implemented
        int my_id;
};

#endif