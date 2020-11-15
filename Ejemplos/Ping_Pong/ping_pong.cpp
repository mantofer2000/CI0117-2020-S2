#include <mpi.h>
#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char *argv[]){
    
    int my_id, num_processes;
    num_processes = 2;
    
    MPI_Init(&argc, &argv);
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    int message_sent, message_received;
    
    int dest =  my_id ? 0 : 1;


    if(!my_id){
        std :: cout << my_id << " is serving." << std :: endl;
        MPI_Send(&message_sent, 1 /*count*/, MPI_INT, dest /*dest*/, 123 /*message id*/, MPI_COMM_WORLD); 
    }

    while(1){
        MPI_Recv(&message_received, 1 /* count*/, MPI_INT, MPI_ANY_SOURCE /*source*/, 123 /*message id*/, MPI_COMM_WORLD, &status);

        usleep(999999);

        if(my_id){
            std :: cout << "PING" << std :: endl;
        }else{
            std :: cout << "PONG" << std :: endl;
        }

        MPI_Send(&message_sent, 1 /*count*/, MPI_INT, dest /*dest*/, 123 /*message id*/, MPI_COMM_WORLD); 

    }


    MPI_Finalize();

    return 0;
}