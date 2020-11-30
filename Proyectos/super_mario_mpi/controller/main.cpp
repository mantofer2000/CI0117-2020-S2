#include "../model/world.h"
#include "../model/element.h"
#include <mpi.h>

int main() {

    // seed for the entire program
    srand (time(NULL));
    // ignorar el proceso 0
    // mpi rank 

    // vectores de info
    // el de monedas -> marios activos
    // vector de marios activos
    // vector de marios attacker
    // vector de enemigos por recibir



    // if mario parametrado
    // 

    // local variables
    Little_Goomba my_goomba;
    Coin my_coin;
    Hole hole;  
    Koopa_Troopa my_koopa;

    World my_world;
    Mario my_mario;

    int position = 0;
    
    // 0 3 3 
    //   
    //
    //
    //


    //
    //
    //
    //
    //


    while (my_mario.is_active()) {
        // all gather vector monedas


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
                            // metodo de enviar
                        } else {
                            my_world.remove_koopa((position + 1) % 100);
                        }
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
    }

 
    return 0;

}