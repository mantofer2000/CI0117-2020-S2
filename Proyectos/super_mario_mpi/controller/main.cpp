#include "../model/coin.h"
#include "../model/goomba.h"
#include "../model/hole.h"
#include "../model/koopa.h"
#include "../model/world.h"
#include "../model/element.h"

int main() {

    srand (time(NULL));

    Little_Goomba my_goomba;
    Coin my_coin;
    Hole hole; // 
    Koopa_Troopa my_koopa;

    World my_world;
    Mario my_mario;

    int position = 0;
    while (my_mario.is_active()) {
        std::vector<Element*> position_elements = my_world.get_next_position_elements(position);
        for (auto iteration = position_elements.begin(); iteration != position_elements.end();
            ++iteration) {
                int status = 0;

                if (*(*iteration) == my_coin) {

                    if ((*iteration)->action(my_mario) == ELEMENT_KILLED_BY_MARIO) {
                        // my_world.remove_element(position, iteration);
                    }

                } else {

                    if ((*(*iteration) == my_goomba) || (*(*iteration) == my_koopa)) {

                        if ((*iteration)->action(my_mario) == ELEMENT_KILLED_BY_MARIO) {
                            // my_world.remove_element(position, iteration);
                        } else {
                            if ((*iteration)->action(my_mario) == ELEMENT_KILLED_MARIO) {
                                my_mario.set_inactive();
                                break; // Agregar una condicion en el for para no hacer esto
                            }
                        }

                    } else {

                        if (*(*iteration) == hole) {

                            if ((*iteration)->action(my_mario) == ELEMENT_KILLED_MARIO) {
                                my_mario.set_inactive();
                                break; // Agregar una condicion en el for para no hacer esto x2
                            }

                        }

                    }
                }
                std::cout << '\n';
        }
        position++;
        position = position % 100;
        std::cout << position << '\n';
        // sleep(2);
    }

    /* if (myCoin != myGoomba) {
        std::cout << "Diferrent Elements" << std::endl;
    } */

    // w.print_world_array();

    return 0;

}