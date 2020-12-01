#include "../model/world.h"
#include "../model/element.h"
#include <mpi.h>

int main(int argc, char* argv[]) {

    int my_id, num_processes, mario_status;
    int *coin_array;
    int *active_marios;
    
    num_processes = 2;

    active_marios = new int[num_processes - 1];

    // seed for the entire program
    srand (time(NULL));


    MPI_Init(&argc, &argv);
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    int player_to_view = 0;
    char attack_strategy = '?';

    // Hacer comprobacion de argumentos.
    /*if (argc >= 3) {
        player_to_view = std::stoi(argv[1]);
        attack_strategy = (char)argv[2];
    } else {
        std::cerr << "Usage: super_mario_mpi player_to_view attack_strategy";
        return 1;
    }*/
    // Verificar que player_to_view no sea 0 ni mayor a la cantidad de procesos.

    if (my_id != 0) {
        

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
        
        while (my_mario.is_active()) {

            // all gather vector monedas

            std::vector<Element*> world_position_elements = my_world.get_next_position_elements(position);
            int elements_count = world_position_elements.size();
            
            // OJO: Como el metodo action es el que imprime lo que esta haciendo Mario,
            // hay que mandarle el my_id para que imprima cual Mario es
            if (elements_count == 0) {
                std::cout <<"Mario #" << my_id << " | ";
                std::cout << "World pos. " << position << ": ";
                // "Mario " << my_id << " is walking. "
                std::cout << "Mario is walking. ";
                std::cout << "Coins: " << my_mario.get_coins_amount() << ' ';

                // Imprimir info de MPI: Attacking, Being attacked by, Attack Strategy, Total Playing.

                std::cout << '\n';

            } else {
                for (int element_position = 0;
                    (element_position < elements_count) && (my_mario.is_active()); ++element_position) {
                    int status = 0;

                    std::cout << "World pos. " << position << ": ";

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
                    std::cout << "Coins: " << my_mario.get_coins_amount() << ' ';

                    // Imprimir info de MPI: Attacking, Being attacked by, Attack Strategy, Total Playing.

                    std::cout << '\n';
                }
            }

            if (my_mario.is_active()) {
                position++;
                position = position % 100;
            } else {
                std::cout << "World pos. " << position << ": Mario Game Over.\n";
            }
            
        }
        
    }
    MPI_Finalize();


    delete active_marios;

    return 0;

}