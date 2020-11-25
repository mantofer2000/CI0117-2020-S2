#include "../model/world.h"

World::World() {
    this->initialize_world();
}

void World::initialize_world() {
    // int index = 0;
    Coin coin;
    Little_Goomba goomba;
    Hole hole;
    Koopa_Troopa koopa;

    // 
    this->world_array.resize(100);

    this->world_array[8].push_back(coin);

    this->world_array[11].push_back(coin);
    this->world_array[11].push_back(coin);
    this->world_array[11].push_back(goomba);

    this->world_array[20].push_back(goomba);

    this->world_array[25].push_back(goomba);
    this->world_array[26].push_back(goomba);

    this->world_array[34].push_back(hole);
    this->world_array[35].push_back(hole);

    this->world_array[40].push_back(goomba);
    this->world_array[41].push_back(goomba);

    this->world_array[43].push_back(hole);
    this->world_array[44].push_back(hole);

    this->world_array[47].push_back(coin);
    this->world_array[47].push_back(coin);

    this->world_array[48].push_back(goomba);
    this->world_array[49].push_back(goomba);

    this->world_array[53].push_back(coin);
    this->world_array[53].push_back(koopa);

    this->world_array[54].push_back(coin);
    this->world_array[56].push_back(coin);

    this->world_array[57].push_back(goomba);
    this->world_array[58].push_back(goomba);
    this->world_array[62].push_back(goomba);
    this->world_array[63].push_back(goomba);
    this->world_array[64].push_back(goomba);
    this->world_array[65].push_back(goomba);

    this->world_array[76].push_back(hole);
    this->world_array[77].push_back(hole);

    this->world_array[85].push_back(coin);

    this->world_array[87].push_back(goomba);
    this->world_array[88].push_back(goomba);

}