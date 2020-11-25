#ifndef ELEMENT_H
#define ELEMENT_H

#include "mario.h"

#define LITTLE_GOOMBA "Little_Goomba"
#define COIN "Coin"
#define KOOPA_TROOPA "Koopa_Troopa"
#define HOLE "Hole"


class Element {
    public:
        virtual void action(Mario &) = 0;

        // Operators
        bool operator==(const Element &other) {
            return this->element_type == other.element_type;
        };

        bool operator!=(const Element &other) {
            return this->element_type != other.element_type;
        };
    
    
    protected:
        std::string element_type;
};


#endif