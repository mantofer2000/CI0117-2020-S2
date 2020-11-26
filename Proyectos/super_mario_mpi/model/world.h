#ifndef WORLD_H
#define WORLD_H

//#include "element.h"
#include "coin.h"
#include "goomba.h"
#include "hole.h"
#include "koopa.h"

#include <iostream>
#include <vector>
#include <list>

class World {
    public:
        World();
        //~World();

        void initialize_world();
        std::vector<Element*> get_next_position_elements(int position);
        void add_goomba(Little_Goomba* new_goomba, int world_position);
        void add_koopa(Koopa_Troopa* new_koopa, int world_position);
        void print_world_array();

    private:
        std::vector< std::vector<Element *> > world_array;
};

#endif /* WORLD_H */