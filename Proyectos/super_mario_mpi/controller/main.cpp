#include "../model/world.h"
#include "../model/element.h"
#include <unistd.h>
#include <mpi.h>


void init_array(int * array, int array_len) {
    for (int i = 0; i < array_len; i++)
        array[i] = 0;
}

void attacking_array(int * array, int array_len) {
    for (int i = 0; i < array_len; i++)
        array[i] = -1;
}

int find_less_coin(int* coin_array, int num_processes) {
    int process = -1;
    for (int i = 0; i < num_processes; i++){
        if (process < 0) {
            if (coin_array[i] >= 0) {
                process = i;
            }
        } else {
            if (coin_array[i] < coin_array[process]) {
                process = i;
            }
        }
    }
    return process;
}

int find_more_coin(int* coin_array, int num_processes) {
    int process = -1;
    for (int i = 0; i < num_processes; i++){
        if (process < 0) {
            if (coin_array[i] >= 0) {
                process = i;
            }
        } else {
            if (coin_array[i] > coin_array[process]) {
                process = i;
            }
        }
    }
    return process;
}


bool remaining_still_alive(int* active_marios, int num_processes) {
    for (int index = 0; index < num_processes - 1; ++index) {
        if (active_marios[index] == 1) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {

    int my_id, num_processes, mario_status, players_alive;
    int *coin_array;
    int *active_marios;
    int *attackers;

    int *attacking_array;
    
    num_processes = 2;

    MPI_Init(&argc, &argv);
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    int player_to_view = 3;
    char attack_strategy = 'R';

    // Hacer comprobacion de argumentos.
    /*if (argc >= 3) {
        player_to_view = std::stoi(argv[1]);

        // Verificar que player_to_view no sea 0 ni mayor a la cantidad de procesos.
        if (player_to_view == 0 || player_to_view >= num_processes) {
            std::cerr << "Invalid player.\n";
            return 3;
        }

        attack_strategy = (char)argv[2];

        if (attack_strategy != 'R' && attack_strategy != 'L'
            && attack_strategy != 'M' && attack_strategy != 'A') {

            std::cerr << "Attack strategies: R L M A\n";
            return 2;

        }

    } else {
        std::cerr << "Usage: super_mario_mpi player_to_view attack_strategy";
        return 1;
    }*/

    // seed for the entire program. Funciona?
    
    //double seed = time(NULL) * (my_id * 10000);
    //std::cout << seed << '\n';
    //srand (seed);

    // Son de tamano num_processes porque el allgather no puede ignorar al 0.
    coin_array = new int[num_processes];

    active_marios = new int[num_processes];
    attackers = new int[num_processes];
    
    attacking_array = new int[num_processes];

    players_alive = 0;

    for (int index = 1; index < num_processes; ++index) {
        active_marios[index] = 1;
    }

    if (my_id == 0) {
        mario_status = 0;
        int coins = 0;
        int attacking = 0;
        while (remaining_still_alive(active_marios, num_processes)) {

            MPI_Bcast(&player_to_view, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Allreduce(&mario_status, &players_alive, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

            MPI_Allgather(&coins, 1, MPI_INT, coin_array, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&mario_status, 1, MPI_INT, active_marios, 1, MPI_INT, MPI_COMM_WORLD);

            if (active_marios[player_to_view] == 0) {
                std::cout << "Enter the number of another player: ";
                std::cin >> player_to_view;
            }
        }
    }

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

        if (my_id == player_to_view) {
            my_mario.set_attack_strategy(attack_strategy);
        }

        int new_goombas = 0;
        int send_goombas = 0;
        int new_koopas = 0;
        int send_koopas = 0;

        Little_Goomba* goomba_pointer = new Little_Goomba();
        *goomba_pointer = my_goomba;


        int my_attacker = 0;
        int id_to_attack = 0;
        int message = 0;

        int position = 0;
        
        while (my_mario.is_active()) {

            mario_status = 1;
            int coins = my_mario.get_coins_amount();
            std::string my_attack_strategy = my_mario.get_attack_strategy();

            // all gather vector monedas

            MPI_Bcast(&player_to_view, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Allreduce(&mario_status, &players_alive, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

            MPI_Allgather(&coins, 1, MPI_INT, coin_array, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&mario_status, 1, MPI_INT, active_marios, 1, MPI_INT, MPI_COMM_WORLD);

            /*if (being_attacked[my_id] == 1) {
                // Reciba el id de quien lo esta atacando.
                MPI_Recv(&my_attacker, 1, MPI_INT, MPI_ANY_SOURCE, 120, MPI_COMM_WORLD, &status);
                // Reciba la cantidad de goombas que tiene que meter en su mundo.
                MPI_Recv(&new_goombas, 1, MPI_INT, my_attacker, 130, MPI_COMM_WORLD, &status);

                while (new_goombas > 0) {
                    my_world.add_goomba(goomba_pointer, (position + 10) % 100);
                    --new_goombas;
                }
            }*/

            std::vector<Element*> world_position_elements = my_world.get_next_position_elements(position);
            int elements_count = world_position_elements.size();
            
            if (/*my_id == player_to_view &&*/ elements_count == 0) {

                std::cout << "World pos. " << position << ": ";
                std::cout << "Mario #" << my_id << " is walking. ";
                std::cout << "Coins: " << coins << " | ";

                // Imprimir info de MPI: Attacking, Being attacked by, Attack Strategy, Total Playing.
                std::cout << "attacking #- | ";
                std::cout << "being attacked by #- | ";
                std::cout << "attack strategy: " << my_attack_strategy << " | ";
                std::cout << "Total playing: " << players_alive;

                std::cout << '\n';

            } else {
                for (int element_position = 0;
                    (element_position < elements_count) && (my_mario.is_active()); ++element_position) {
                    int status = 0;

                    //if (my_id == player_to_view) {
                        std::cout << "World pos. " << position << ": ";
                    //}

                    if (*world_position_elements[element_position] == my_coin) {

                        if (world_position_elements[element_position]->action(my_mario)
                            == ELEMENT_KILLED_BY_MARIO) {

                            my_world.remove_coin((position + 1) % 100);
                            //if (my_id == player_to_view) {
                                std::cout << "Mario #" << my_id << " jumped and grabbed a coin! ";
                            //}

                        } else {
                            //if (my_id == player_to_view) {
                                std::cout << "Mario #" << my_id << " didn't jump and ingored the coin! ";
                            //}
                        }

                    } else {

                        if ((*world_position_elements[element_position] == my_goomba)
                            || (*world_position_elements[element_position] == my_koopa)) {

                            int action = world_position_elements[element_position]->action(my_mario);
                            if (action == ELEMENT_KILLED_BY_MARIO) {

                                if (*world_position_elements[element_position] == my_goomba) {

                                    my_world.remove_goomba((position + 1) % 100);
                                    //if (my_id == player_to_view) {
                                        std::cout   << "Mario #" << my_id
                                                    << " jumped and killed a little goomba! ";
                                    //}
                                    // metodo de enviar
                                    if (my_attack_strategy == RANDOM_STRG) {
                                        // Escoger un jugador vivo aleatoriamente y enviar mensaje.
                                    } else {
                                        if (my_attack_strategy == L_COIN_STRG) {
                                            int minimum = 1;
                                            for (int index = 2; index < num_processes; ++index) {
                                                if (coin_array[index] < coin_array[minimum]) {
                                                    if (active_marios[index] == 1) {
                                                        minimum = index;
                                                    }
                                                }
                                            }
                                            id_to_attack = minimum;
                                        } else {
                                            if (my_attack_strategy == M_COIN_STRG) {
                                                int maximum = 1;
                                                for (int index = 2; index < num_processes; ++index) {
                                                    if (coin_array[index] > coin_array[maximum]) {
                                                        if (active_marios[index] == 1) {
                                                            maximum = index;
                                                        }
                                                    }
                                                }
                                                id_to_attack = maximum;
                                            } else {
                                                if (my_attack_strategy == ATTACKER_STRG) {
                                                    
                                                    /*for (int index = 1; index < num_processes; ++index) {
                                                        if (attackers[index] == 1) {

                                                        }
                                                    }*/

                                                }
                                            }
                                        }
                                    }
                                    // Que cada proceso tenga una variable 
                                    // que se reciba siempre el numero de goombas
                                    // que va a recibir, o algo asi
                                    // Tipo si no va a recibir nada, que ahi reciba un 0.
                                    /*message = my_id;
                                    MPI_Send(&message, 1, MPI_INT, id_to_attack, 120, MPI_COMM_WORLD);
                                    new_goombas = 1;
                                    MPI_Send(&new_goombas, 1, MPI_INT, id_to_attack, 130, MPI_COMM_WORLD);*/

                                } else {

                                    my_world.remove_koopa((position + 1) % 100);
                                    //if (my_id == player_to_view) {
                                        std::cout   << "Mario #" << my_id
                                                    << " jumped and killed a koopa troopa! ";
                                    //}
                                    // Enviar koopa

                                }

                            } else {
                                if (action == ELEMENT_KILLED_MARIO) {
                                    //if (my_id == player_to_view) {

                                        if (*world_position_elements[element_position] == my_goomba) {
                                            std::cout   << "Mario #" << my_id
                                                        << " didn't jump and was killed by a little goomba! ";
                                        } else {
                                            std::cout   << "Mario #" << my_id
                                                        << " didn't jump and was killed by a koopa troopa! ";
                                        }

                                    //}

                                    my_mario.set_inactive();
                                } else {
                                    //if (my_id == player_to_view) {

                                        if (*world_position_elements[element_position] == my_goomba) {
                                            std::cout   << "Mario #" << my_id
                                                        << " jumped and passed a little goomba! ";
                                        } else {
                                            std::cout   << "Mario #" << my_id
                                                        << " jumped and passed a koopa troopa! ";
                                        }

                                    //}
                                }
                            }

                        } else {

                            if (*world_position_elements[element_position] == hole) {

                                if (world_position_elements[element_position]->action(my_mario)
                                    == ELEMENT_KILLED_MARIO) {

                                    //if (my_id == player_to_view) {
                                        std::cout   << "Mario #" << my_id
                                                    << " didn't jump the hole and had a brutal death! ";
                                    //}

                                    my_mario.set_inactive();

                                } else {
                                    //if (my_id == player_to_view) {
                                        std::cout << "Mario jumped and passed the hole! ";
                                    //}
                                }

                            }

                        }
                    }
                    //if (my_id == player_to_view) {
                        std::cout << "Coins: " << my_mario.get_coins_amount() << ' ';

                        // Imprimir info de MPI: Attacking, Being attacked by, Attack Strategy, Total Playing.

                        std::cout << '\n';
                    //}
                }
            }

            if (my_mario.is_active()) {
                position++;
                position = position % 100;
            } else {
                mario_status = 0;
                if (my_id == player_to_view) {
                    std::cout << "World pos. " << position << ": Mario #" << my_id << " Game Over.\n";
                }
            }
            // sleep(2);
            
        }
        
        while (remaining_still_alive(active_marios, num_processes)) {
            int coins = my_mario.get_coins_amount();

            MPI_Bcast(&player_to_view, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Allreduce(&mario_status, &players_alive, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

            MPI_Allgather(&coins, 1, MPI_INT, coin_array, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&mario_status, 1, MPI_INT, active_marios, 1, MPI_INT, MPI_COMM_WORLD);

        }

    }

    

    MPI_Finalize();


    delete active_marios;

    return 0;

}