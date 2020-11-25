#ifndef ELEMENT_H
#define ELEMENT_H

#include <mario.h>

#define LITTLE_GOOMBA = "Little_Goomba"
#define COIN = "Coin"
#define KOOPA_TROOPA = "Koopa_Troopa"
#define HOLE = "Hole"


class Element {
    public:
        virtual void action(Mario &) = 0;
    
    protected:
        std::string element_type;
};


#endif