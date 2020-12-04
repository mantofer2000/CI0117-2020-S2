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

int find_less_coin(int* active_marios, int* coin_array, int num_processes, int my_id) {
    int process = -1;
    for (int i = 1; i < num_processes; i++) {
        if (i != my_id) {
            if (process < 0) {
                if (coin_array[i] >= 0) {
                    process = i;
                }
            } else {
                if (active_marios[i] == 1) {
                    if (coin_array[i] < coin_array[process]) {
                        process = i;
                    }
                }
            }
        }
    }
    return process;
}

int find_more_coin(int* active_marios, int* coin_array, int num_processes, int my_id) {
    int process = -1;
    for (int i = 1; i < num_processes; i++) {
        if (i != my_id) {
            if (process < 0) {
                if (coin_array[i] >= 0) {
                    process = i;
                }
            } else {
                if (active_marios[i] == 1) {
                    if (coin_array[i] > coin_array[process]) {
                        process = i;
                    }
                }
            }
        }
    }
    return process;
}


bool remaining_still_alive(int* active_marios, int num_processes) {
    for (int index = 1; index < num_processes; ++index) {
        if (active_marios[index] == 1) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {

    int my_id, num_processes, mario_status, players_alive, num_attackers_strat;
    int *coin_array;
    int *active_marios;
    int *attackers;
    // goombas every process has to receive
    int *goombas;
    // koopas every process has to receive
    int *koopas;
    int *attacking_array;
    
    num_processes = 2;

    MPI_Init(&argc, &argv);
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    int player_to_view = 0;
    char attack_strategy = '?';

    // Hacer comprobacion de argumentos.
    if (argc >= 3) {
        player_to_view = std::stoi(argv[1]);

        // Verificar que player_to_view no sea 0 ni mayor a la cantidad de procesos.
        if (player_to_view == 0 || player_to_view >= num_processes) {
            if (my_id == 0) {
                std::cerr << "Invalid player.\n";
            }
            return 3;
        }

        attack_strategy = (argv[2])[0];

        if (attack_strategy != 'R' && attack_strategy != 'L'
            && attack_strategy != 'M' && attack_strategy != 'A') {

            if (my_id == 0) {
                std::cerr << "Attack strategies: R L M A\n";
            }
            return 2;

        }

    } else {
        if (my_id == 0) {
            std::cerr << "Usage: super_mario_mpi player_to_view attack_strategy";
        }
        return 1;
    }

    // Son de tamano num_processes porque el allgather no puede ignorar al 0.
    coin_array = new int[num_processes];
    active_marios = new int[num_processes];
    attackers = new int[num_processes];
    attacking_array = new int[num_processes];
    goombas = new int[num_processes];
    koopas = new int[num_processes];

    players_alive = 0;
    num_attackers_strat = 0;

    for (int index = 1; index < num_processes; ++index) {
        active_marios[index] = 1;
    }

    if (my_id == 0) {
        mario_status = 0;
        int coins = 0;
        int attacker_strat = 0;
        int id_to_attack = 0;
        int goombas_to_send = 0;
        int koopas_to_send = 0;
        while (remaining_still_alive(active_marios, num_processes)) {
            MPI_Bcast(&player_to_view, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Allreduce(&mario_status, &players_alive, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
            MPI_Allreduce(&attacker_strat, &num_attackers_strat, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

            MPI_Allgather(&coins, 1, MPI_INT, coin_array, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&mario_status, 1, MPI_INT, active_marios, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&id_to_attack, 1, MPI_INT, attacking_array, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&attacker_strat, 1, MPI_INT, attackers, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&goombas_to_send, 1, MPI_INT, goombas, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&koopas_to_send, 1, MPI_INT, koopas, 1, MPI_INT, MPI_COMM_WORLD);
            
            if (remaining_still_alive(active_marios, num_processes)) {
                while (active_marios[player_to_view] == 0) {
                    std::cout << "He dead. Enter the number of another player: ";
                    std::cin >> player_to_view;
                }
            }
        }
    }

    if (my_id != 0) {
        Little_Goomba my_goomba;
        Coin my_coin;
        Hole hole;  
        Koopa_Troopa my_koopa;

        World my_world;

        Mario my_mario(my_id);

        if (my_id == player_to_view) {
            my_mario.set_attack_strategy(attack_strategy);
        }

        int new_goombas = 0;
        int goombas_to_send = 0;
        int new_koopas = 0;
        int koopas_to_send = 0;

        int coins = 0;
        int my_attacker = 0;
        int attacker_strat = 0;
        int id_to_attack = 0;
        int message = 0;

        int position = 0;
        
        while (my_mario.is_active()) {

            mario_status = 1;
            coins = my_mario.get_coins_amount();
            std::string my_attack_strategy = my_mario.get_attack_strategy();

            if (my_attack_strategy == ATTACKER_STRG) {
                attacker_strat = 1;
            }

            MPI_Bcast(&player_to_view, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Allreduce(&mario_status, &players_alive, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
            MPI_Allreduce(&attacker_strat, &num_attackers_strat, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

            MPI_Allgather(&coins, 1, MPI_INT, coin_array, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&mario_status, 1, MPI_INT, active_marios, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&id_to_attack, 1, MPI_INT, attacking_array, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&attacker_strat, 1, MPI_INT, attackers, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&goombas_to_send, 1, MPI_INT, goombas, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&koopas_to_send, 1, MPI_INT, koopas, 1, MPI_INT, MPI_COMM_WORLD);

            for (int index = 1; index < num_processes; ++index) {
                if (attacking_array[index] == my_id) {
                    my_attacker = index; // Ese proceso me esta atacando.
                    // Ver cuantos goombas y koopas me esta mandando.
                    int count_goombas = 0, count_koopas = 0;
                    while (count_goombas < goombas[index]) {
                        my_world.add_goomba(position);
                        ++count_goombas;
                    }
                    while (count_koopas < koopas[index]) {
                        my_world.add_koopa(position);
                        ++count_koopas;
                    }
                }
            }

            if (active_marios[id_to_attack] == 0) {
                id_to_attack = 0;
            }

            if (active_marios[my_attacker] == 0) {
                my_attacker = 0;
            }

            goombas_to_send = 0;
            koopas_to_send = 0;

            std::vector<Element*> world_position_elements = my_world.get_next_position_elements(position);
            int elements_count = world_position_elements.size();
            
            if (my_id == player_to_view && elements_count == 0) {

                std::cout << "World pos. " << position << ": ";
                std::cout << "Mario #" << my_id << " is walking. ";
                std::cout << "Coins: " << coins << " | ";

                // Imprimir info de MPI: Attacking, Being attacked by, Attack Strategy, Total Playing.
                std::cout << "attacking #" << id_to_attack << " | ";
                std::cout << "being attacked by #" << my_attacker << " | ";
                std::cout << "attack strategy: " << my_attack_strategy << " | ";
                std::cout << "Total playing: " << players_alive;

                std::cout << '\n';

            } else {
                for (int element_position = 0;
                    (element_position < elements_count) && (my_mario.is_active()); ++element_position) {
                    int status = 0;

                    double seed = time(NULL) * (my_id * 10000);
                    srand(seed);
                    int probability = (rand() % 100) + 1;

                    if (my_id == player_to_view) {
                        std::cout << "World pos. " << position << ": ";
                    }

                    if (*world_position_elements[element_position] == my_coin) {

                        if (world_position_elements[element_position]->action(my_mario, probability)
                            == ELEMENT_KILLED_BY_MARIO) {

                            my_world.remove_coin((position + 1) % 100);
                            if (my_id == player_to_view) {
                                std::cout << "Mario #" << my_id << " jumped and grabbed a coin! ";
                            }

                        } else {
                            if (my_id == player_to_view) {
                                std::cout << "Mario #" << my_id << " didn't jump and ingored the coin! ";
                            }
                        }

                    } else {

                        if ((*world_position_elements[element_position] == my_goomba)
                            || (*world_position_elements[element_position] == my_koopa)) {

                            int action = world_position_elements[element_position]->action(my_mario, probability);
                            if (action == ELEMENT_KILLED_BY_MARIO) {

                                if (*world_position_elements[element_position] == my_goomba) {

                                    my_world.remove_goomba((position + 1) % 100);
                                    if (my_id == player_to_view) {
                                        std::cout   << "Mario #" << my_id
                                                    << " jumped and killed a little goomba! ";
                                    }
                                    // metodo de enviar
                                    if (players_alive > 1)
                                    {
                                        if (my_attack_strategy == RANDOM_STRG) {
                                            // Escoger un jugador vivo aleatoriamente y enviar mensaje.
                                            do {
                                                id_to_attack = (rand() % (num_processes - 1)) + 1;
                                            } while (active_marios[id_to_attack] == 0 || id_to_attack == my_id);

                                        } else {

                                            if (my_attack_strategy == L_COIN_STRG) {
                                                id_to_attack = find_less_coin(active_marios, coin_array, num_processes, my_id);
                                            } else {
                                                if (my_attack_strategy == M_COIN_STRG) {
                                                    id_to_attack = find_more_coin(active_marios, coin_array, num_processes, my_id);
                                                } else {
                                                    if (my_attack_strategy == ATTACKER_STRG) {
                                                        if (num_attackers_strat > 1) {
                                                            do {
                                                                id_to_attack = (rand() % (num_processes - 1)) + 1;
                                                            } while (active_marios[id_to_attack] == 0 || attackers[id_to_attack] == 0
                                                                || id_to_attack == my_id);
                                                        }
                                                    }
                                                }
                                            }

                                        }
                                        ++goombas_to_send;
                                    }

                                } else {

                                    my_world.remove_koopa((position + 1) % 100);
                                    if (my_id == player_to_view) {
                                        std::cout   << "Mario #" << my_id
                                                    << " jumped and killed a koopa troopa! ";
                                    }
                                    // Enviar koopa
                                    if (players_alive > 1)
                                    {
                                        if (my_attack_strategy == RANDOM_STRG) {
                                            // Escoger un jugador vivo aleatoriamente y enviar mensaje.
                                            do {
                                                id_to_attack = (rand() % (num_processes - 1)) + 1;
                                            } while (active_marios[id_to_attack] == 0 || id_to_attack == my_id);

                                        } else {

                                            if (my_attack_strategy == L_COIN_STRG) {
                                                id_to_attack = find_less_coin(active_marios, coin_array, num_processes, my_id);
                                            } else {
                                                if (my_attack_strategy == M_COIN_STRG) {
                                                    id_to_attack = find_more_coin(active_marios, coin_array, num_processes, my_id);
                                                } else {
                                                    if (my_attack_strategy == ATTACKER_STRG) {
                                                        if (num_attackers_strat > 1) {
                                                            do {
                                                                id_to_attack = (rand() % (num_processes - 1)) + 1;
                                                            } while (active_marios[id_to_attack] == 0 || attackers[id_to_attack] == 0
                                                                || id_to_attack == my_id);
                                                        }
                                                    }
                                                }
                                            }

                                        }
                                        ++koopas_to_send;
                                    }
                                }

                            } else {
                                if (action == ELEMENT_KILLED_MARIO) {
                                    if (my_id == player_to_view) {

                                        if (*world_position_elements[element_position] == my_goomba) {
                                            std::cout   << "Mario #" << my_id
                                                        << " didn't jump and was killed by a little goomba! ";
                                        } else {
                                            std::cout   << "Mario #" << my_id
                                                        << " didn't jump and was killed by a koopa troopa! ";
                                        }

                                    }

                                    my_mario.set_inactive();
                                } else {
                                    if (my_id == player_to_view) {

                                        if (*world_position_elements[element_position] == my_goomba) {
                                            std::cout   << "Mario #" << my_id
                                                        << " jumped and passed a little goomba! ";
                                        } else {
                                            std::cout   << "Mario #" << my_id
                                                        << " jumped and passed a koopa troopa! ";
                                        }

                                    }
                                }
                            }

                        } else {

                            if (*world_position_elements[element_position] == hole) {

                                if (world_position_elements[element_position]->action(my_mario, probability)
                                    == ELEMENT_KILLED_MARIO) {

                                    if (my_id == player_to_view) {
                                        std::cout   << "Mario #" << my_id
                                                    << " didn't jump the hole and had a brutal death! ";
                                    }

                                    my_mario.set_inactive();

                                } else {
                                    if (my_id == player_to_view) {
                                        std::cout   << "Mario #" << my_id
                                                    << " jumped and passed the hole! ";
                                    }
                                }

                            }

                        }
                    }
                    if (my_id == player_to_view) {
                        std::cout << "Coins: " << my_mario.get_coins_amount() << " | ";

                        // Imprimir info de MPI: Attacking, Being attacked by, Attack Strategy, Total Playing.
                        std::cout << "attacking #" << id_to_attack << " | ";
                        std::cout << "being attacked by #" << my_attacker << " | ";
                        std::cout << "attack strategy: " << my_attack_strategy << " | ";
                        std::cout << "Total playing: " << players_alive;

                        std::cout << '\n';
                    }
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
                if (my_attack_strategy == ATTACKER_STRG) {
                    attacker_strat = 0;
                }
            }
            sleep(2);
            
        }
        
        while (remaining_still_alive(active_marios, num_processes)) {
            coins = my_mario.get_coins_amount();
            id_to_attack = 0;
            goombas_to_send = 0;
            koopas_to_send = 0;

            MPI_Bcast(&player_to_view, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Allreduce(&mario_status, &players_alive, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
            MPI_Allreduce(&attacker_strat, &num_attackers_strat, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

            MPI_Allgather(&coins, 1, MPI_INT, coin_array, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&mario_status, 1, MPI_INT, active_marios, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&id_to_attack, 1, MPI_INT, attacking_array, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&attacker_strat, 1, MPI_INT, attackers, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&goombas_to_send, 1, MPI_INT, goombas, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Allgather(&koopas_to_send, 1, MPI_INT, koopas, 1, MPI_INT, MPI_COMM_WORLD);
        }

    }
    MPI_Finalize();


    delete[] active_marios;
    delete[] coin_array;
    delete[] active_marios;
    delete[] attackers;
    delete[] attacking_array;
    delete[] goombas;
    delete[] koopas;
   

    return 0;

}