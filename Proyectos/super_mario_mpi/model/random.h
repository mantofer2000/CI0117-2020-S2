#ifndef RAD
#define RAD

#include <bits/stdc++.h>

class Rand_Gen {
    public:
        double get_rand_double();
        Rand_Gen();
    
    private: 
        double seed;
};


#endif