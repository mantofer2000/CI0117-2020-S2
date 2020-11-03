#include <omp.h>
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

int main(int argc, char* arg[]){
    size_t number;
    bool answer;
    if(argc >= 2){
        number = (size_t)strtoul(arg[1], NULL, 10);
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }
   
    answer = is_prime(number);
    if(answer){
        std :: cout << number << " is prime." << std :: endl;
    }else{
        std :: cout << number << " is not prime." << std :: endl;
    }


   return 0; 
}