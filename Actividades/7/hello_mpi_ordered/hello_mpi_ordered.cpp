#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[]) {

    int my_id, num_processes;

    MPI_Init(&argc, &argv);
    
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    int message_sent = 1;
    int message_received = 0;

    if(my_id == 0){
        MPI_Send(&message_sent, 1 /*count*/, MPI_INT, message_sent /*dest*/, 123 /*message id*/, MPI_COMM_WORLD);
    }

    if(my_id != 0){
        MPI_Recv(&message_received, 1 /* count*/, MPI_INT, 0 /*source*/, 123 /*message id*/, MPI_COMM_WORLD, &status);
        message_received = my_id + 1;
        
        if(message_received < num_processes){
            MPI_Send(&message_received, 1 /*count*/, MPI_INT, message_received /*dest*/, 123 /*message id*/, MPI_COMM_WORLD);
        }

    }


    cout << "Hello. I am process: " << my_id << ". Total processes: " << num_processes << endl;


    MPI_Finalize();

    return 0;
}