#ifndef ELEMENT_H
#define ELEMENT_H

#include "mario.h"
<<<<<<< HEAD

=======
>>>>>>> a12aa01cde9b7ecff9744cc872601490adf06364

#define LITTLE_GOOMBA "Little_Goomba"
#define COIN "Coin"
#define KOOPA_TROOPA "Koopa_Troopa"
#define HOLE "Hole"

#define ELEMENT_KILLED_MARIO 1
#define ELEMENT_KILLED_BY_MARIO 2
#define ELEMENT_IGNORED_BY_MARIO 3


class Element {
    public:
        virtual int action(Mario &, int probability) = 0;

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