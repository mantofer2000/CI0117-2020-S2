#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[]) {

    int my_id, num_processes;

    MPI_Init(&argc, &argv);
    
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);


    int message_received = 0;
    if(my_id != 0){
        MPI_Recv(&message_received, 1 /* count*/, MPI_INT, 0 /*source*/, 123 /*message id*/, MPI_COMM_WORLD, &status);
    }
    cout << "Hello. I am process: " << my_id << ". Total processes: " << num_processes << endl;


    if(my_id == 0){
        int message_sent = 0;
        for(int i = 1; i < num_processes; i++){
            MPI_Send(&message_sent, 1 /*count*/, MPI_INT, i /*dest*/, 123 /*message id*/, MPI_COMM_WORLD);
        }
    }




    MPI_Finalize();

    return 0;
}