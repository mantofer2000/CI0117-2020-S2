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

    Coin* coin_pointer = new Coin();
    *coin_pointer = coin;

    Little_Goomba* goomba_pointer = new Little_Goomba();
    *goomba_pointer = goomba;

    Hole* hole_pointer = new Hole();
    *hole_pointer = hole;

    Koopa_Troopa* koopa_pointer = new Koopa_Troopa();
    *koopa_pointer = koopa;

    // 
    this->world_array.resize(100);

    this->world_array[8].push_back(coin_pointer);

    this->world_array[11].push_back(coin_pointer);
    this->world_array[11].push_back(coin_pointer);
    this->world_array[11].push_back(goomba_pointer);

    this->world_array[20].push_back(goomba_pointer);

    this->world_array[25].push_back(goomba_pointer);
    this->world_array[26].push_back(goomba_pointer);

    this->world_array[34].push_back(hole_pointer);
    this->world_array[35].push_back(hole_pointer);

    this->world_array[40].push_back(goomba_pointer);
    this->world_array[41].push_back(goomba_pointer);

    this->world_array[43].push_back(hole_pointer);
    this->world_array[44].push_back(hole_pointer);

    this->world_array[47].push_back(coin_pointer);
    this->world_array[47].push_back(coin_pointer);

    this->world_array[48].push_back(goomba_pointer);
    this->world_array[49].push_back(goomba_pointer);

    this->world_array[53].push_back(coin_pointer);
    this->world_array[53].push_back(koopa_pointer);

    this->world_array[54].push_back(coin_pointer);
    this->world_array[56].push_back(coin_pointer);

    this->world_array[57].push_back(goomba_pointer);
    this->world_array[58].push_back(goomba_pointer);
    this->world_array[62].push_back(goomba_pointer);
    this->world_array[63].push_back(goomba_pointer);
    this->world_array[64].push_back(goomba_pointer);
    this->world_array[65].push_back(goomba_pointer);

    this->world_array[76].push_back(hole_pointer);
    this->world_array[77].push_back(hole_pointer);

    this->world_array[85].push_back(coin_pointer);

    this->world_array[87].push_back(goomba_pointer);
    this->world_array[88].push_back(goomba_pointer);
}

void World::add_goomba(int world_position) {
    Little_Goomba goomba;
    Little_Goomba* new_goomba_pointer = new Little_Goomba();
    *new_goomba_pointer = goomba;

    int index = (world_position + 10) % 100;
    this->world_array[index].push_back(new_goomba_pointer);
}

void World::add_koopa(int world_position) {
    Koopa_Troopa koopa;
    Koopa_Troopa* new_koopa_pointer = new Koopa_Troopa();
    *new_koopa_pointer = koopa;

    int index = (world_position + 10) % 100;
    this->world_array[index].push_back(new_koopa_pointer);
}

std::vector<Element*> World::get_next_position_elements(int world_position) {
    return this->world_array[(world_position + 1) % 100];
}

void World::remove_coin(int world_position) {
    Coin a_coin; // Mejor tener un private de estos elementos en la clase.
    bool removed = false;

    for (auto iteration = this->world_array[world_position].begin();
        iteration != this->world_array[world_position].end() && !(removed); ++iteration) {

        if (*(*iteration) == a_coin) {
            this->world_array[world_position].erase(iteration);
            removed = true;
        }

    }
}

void World::remove_goomba(int world_position) {
    Little_Goomba a_goomba;
    bool removed = false;

    for (auto iteration = this->world_array[world_position].begin();
        iteration != this->world_array[world_position].end() && !(removed); ++iteration) {

        if (*(*iteration) == a_goomba) {
            this->world_array[world_position].erase(iteration);
            removed = true;
        }

    }
}

void World::remove_koopa(int world_position) {
    Koopa_Troopa a_koopa;
    bool removed = false;

    for (auto iteration = this->world_array[world_position].begin();
        iteration != this->world_array[world_position].end() && !(removed); ++iteration) {

        if (*(*iteration) == a_koopa) {
            this->world_array[world_position].erase(iteration);
            removed = true;
        }

    }
}

void World::print_world_array() {
    for (int index = 0; index < 100; ++index) {
        int position_size = this->world_array[index].size();

        std::cout << index << ": ";
        if (position_size != 0) {
            for (int element_position = 0; element_position < position_size; ++element_position) {
                // std::cout << this->world_array[index][element_position]->get_element_type() << ' ';
            }
        } else {
            std::cout << "empty";
        }
        std::cout << '\n';
    }
}