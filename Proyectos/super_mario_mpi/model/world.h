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

        void initialize_world();
        
        std::vector<Element*> get_next_position_elements(int position);

        void add_goomba(int world_position);
        void add_koopa(int world_position);

        void remove_coin(int world_position);
        void remove_goomba(int world_position);
        void remove_koopa(int world_position);

    private:
        std::vector< std::vector<Element *> > world_array;
};

#endif /* WORLD_H */