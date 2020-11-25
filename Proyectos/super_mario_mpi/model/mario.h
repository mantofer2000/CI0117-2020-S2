#ifndef MARIO_H
#define MARIO_H

#include <bits/stdc++.h>

class Mario {
    friend class Element;
    public:
        Mario() {};
    
    private:
        // amount of coins
        int coin;
        // bool to know if mario is active or not
        bool active;
        // mpi rank, needs to be implemented
        int my_id;
};

#endif