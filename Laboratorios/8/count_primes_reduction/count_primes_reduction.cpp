#include <mpi.h>
#include <bits/stdc++.h>


bool is_prime(size_t number){
    if ( number < 2 ) return false;
	if ( number == 2 ) return true;
	if ( number % 2 == 0 ) return false;

	for ( size_t i = 3, last = (size_t)(double)sqrt(number); i <= last; i += 2 )
		if ( number % i == 0 )
			return false;

	return true;
}

int count_primes(size_t max_number, int begin, int end, int num_processes)
{
    int count = 0;
    for ( size_t number = begin; number < end; ++number )
        if ( is_prime(number) )
            ++count;

    return count;
}

int main(int argc, char* argv[])
{
    size_t max_number = 0;
    int count = 0;

    int my_id, num_processes, final_result, distribution, begin, end;
    double t1, t2, elapsed, total_elapsed;
    
    MPI_Init(&argc, &argv);
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    if ( my_id == 0 )
    {
        while ( max_number <= 2 )
        {
            std::cout << "Enter max_number: ";
            std::cin >> max_number;

            if ( max_number <= 2 ) std::cerr << "max_number must be greater than 2.\n";
        }
    }

    MPI_Bcast(&max_number, 1, MPI_INT, 0, MPI_COMM_WORLD);

    distribution = ( max_number / num_processes );
    begin = ( distribution * my_id );
    if ( my_id < num_processes - 1 )
        end = begin + distribution;
    else
        end = max_number;

    t1 = MPI_Wtime();
    count = count_primes(max_number, begin, end, num_processes);
    

    MPI_Reduce(&count, &final_result, 1, MPI_INT, MPI_SUM,0, MPI_COMM_WORLD);
    t2 = MPI_Wtime();

    if( !(my_id) )
    {
        std::cout   << final_result << " prime numbers found in range [2, " << max_number << "] in "
                    << ( t2 - t1 ) << " with " << num_processes << " processes. "<< '\n';
    }

    MPI_Finalize();

    return 0; 
}