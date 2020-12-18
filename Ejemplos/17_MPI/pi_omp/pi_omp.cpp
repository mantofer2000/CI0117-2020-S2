#include <iostream>
#include <omp.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    int n, k;

    if (argc > 1) {
        n = stoi(argv[1]);
    } else {
        cout << "Invalid number of parameters.\n";
        return 1;
    }

    double factor = 1.0;
    double sum = 0.0;
    
    #pragma omp parallel for default(none) private(k, factor) shared(n) reduction(+: sum)
    for (int k = 0; k < n; k++) {        
        if (k % 2 == 0) { 
            factor = 1.0;
        } else {
            factor = -1.0;
        }
        sum += factor/(2*k+1);
    }

    double pi = 4 * sum;

    printf("pi is approximately %.16f\n", pi);
    
    return 0;
}