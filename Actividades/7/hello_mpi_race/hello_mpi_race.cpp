#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[]) {
    int my_id, num_processes;
    
    MPI_Init(&argc, &argv);
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    int message_sent, message_received;
    int position = 1;

    if(!my_id){
        // es < por el proceso 0
        while(position < num_processes){
            MPI_Recv(&message_received, 1 /* count*/, MPI_INT, MPI_ANY_SOURCE, 123 /*message id*/, MPI_COMM_WORLD, &status);
            std :: cout << "Process " << message_received << " arrived at position " << position + 1 << std :: endl;
            position++;

        }
    }

    if(my_id){
        MPI_Send(&my_id, 1 /*count*/, MPI_INT, 0 /*dest*/, 123 /*message id*/, MPI_COMM_WORLD);    
    }

    MPI_Finalize();

    return 0;
}