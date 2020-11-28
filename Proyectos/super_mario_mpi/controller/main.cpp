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

        std::cout << "Position: " << position << '\n';
        std::cout << "Coins: " << my_mario.get_coins_amount() << '\n';

        std::vector<Element*> world_position_elements = my_world.get_next_position_elements(position);
        int elements_count = world_position_elements.size();
        
        for (int element_position = 0;
            (element_position < elements_count) && (my_mario.is_active()); ++element_position) {
            int status = 0;

            if (*world_position_elements[element_position] == my_coin) {

                if (world_position_elements[element_position]->action(my_mario)
                    == ELEMENT_KILLED_BY_MARIO) {

                    my_world.remove_coin((position + 1) % 100);

                }

            } else {

                if ((*world_position_elements[element_position] == my_goomba)
                    || (*world_position_elements[element_position] == my_koopa)) {

                    int action = world_position_elements[element_position]->action(my_mario);
                    if (action == ELEMENT_KILLED_BY_MARIO) {

                        if (*world_position_elements[element_position] == my_goomba) {
                            my_world.remove_goomba((position + 1) % 100);
                        } else {
                            my_world.remove_koopa((position + 1) % 100);
                        }
                        // my_world.remove_element(position, iteration);
                    } else {
                        if (action == ELEMENT_KILLED_MARIO) {
                            my_mario.set_inactive();
                        }
                    }

                } else {

                    if (*world_position_elements[element_position] == hole) {

                        if (world_position_elements[element_position]->action(my_mario)
                            == ELEMENT_KILLED_MARIO) {

                            my_mario.set_inactive();

                        }

                    }

                }
            }
            std::cout << '\n';
        }
        position++;
        position = position % 100;
        // sleep(2);
    }

    /* if (myCoin != myGoomba) {
        std::cout << "Diferrent Elements" << std::endl;
    } */

    // w.print_world_array();

    return 0;

}