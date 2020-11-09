#include <omp.h>
#include <bits/stdc++.h>


bool is_prime(size_t number){
    //bool value = true;
    
    if ( number < 2 ) return false;
	if ( number == 2 ) return true;
	if ( number % 2 == 0 ) return false;

    //size_t last = (size_t)(double)sqrt(number);

    for ( size_t i = 3, last = (size_t)(double)sqrt(number); i <= last; i += 2 )
		if ( number % i == 0 )
			return false;

	return true;
}

int count_primes(size_t max_number)
{
    int count = 0;
    #pragma omp parallel for default(none) shared(max_number) reduction(+: count) schedule(runtime)
    for ( size_t number = 3; number < max_number; ++number ){
        if ( is_prime(number) ){
            ++count;
        }
    }
    return count;
}

int main(int argc, char* argv[])
{
    size_t max_number = 0;
    int count = 0;

    if( argc >= 2 ) {
        max_number = (size_t) strtoul(argv[1], NULL, 10);

        if ( max_number <= 2 ) {
            std::cerr << "Error, max_number must be greater than 2.\n";
            return 2;
        }    
    } else {
        std::cerr << "Error, invalid number of parameters\n";
        return 1;
    }

    count = count_primes(max_number);

    std::cout << "There are " << count << " prime numbers between 2 and " << max_number << '\n';

    return 0; 
}