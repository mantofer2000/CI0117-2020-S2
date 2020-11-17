#include <mpi.h>
#include <bits/stdc++.h>

int main(int argc, char *argv[]){
    
  

    int my_id, num_processes, array_size, random_num, random_array_index, 
    send, receive, result, min_num, max_num, average_num;

    int * array;
    
    MPI_Init(&argc, &argv);
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);


    srand(time(NULL) * my_id * 1000); /* Initialize seed */

    if(!my_id){
        std :: cout << "Please enter the number of values: " << std :: endl;
        std :: cin >> array_size;
        std :: cout << "Please enter " << array_size << " integer values: " << std :: endl;
        
        array = new int[array_size];
        
        for(int i = 0; i < array_size; i++){
            std :: cin >> array[i];
        }

    }
    MPI_Bcast(&array_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(my_id){array = new int[array_size];}
    
    MPI_Bcast(array, array_size, MPI_INT, 0, MPI_COMM_WORLD);

    random_num = array[rand() % array_size];

    MPI_Reduce(&random_num, &min_num, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&random_num, &max_num, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&random_num, &average_num, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(!my_id){average_num /= array_size;}
    



    //std :: cout << my_id << " - " << random_num << std::endl;

    // seccion serial por los imprimir
    
    if (my_id != 0){
        MPI_Recv(&receive, 1 /* count*/, MPI_INT, my_id - 1 /*source*/, 123 /*message id*/, MPI_COMM_WORLD, &status);
    }

    std :: cout << "process: " << my_id << " I chose number " << random_num << std :: endl;
    
    if(!my_id){
        std :: cout << "process: " << my_id << " Minimun is " << min_num << std :: endl;
        std :: cout << "process: " << my_id << " Maximun is " << max_num << std :: endl;
        std :: cout << "process: " << my_id << " Average is " << average_num << std :: endl;
    }


	if ( my_id < num_processes - 1 ) {
        MPI_Send(&send, 1 /*count*/, MPI_INT, my_id + 1 /*dest*/, 123 /*message id*/, MPI_COMM_WORLD);
    }

    delete[] array;

    MPI_Finalize();

    return 0;
}