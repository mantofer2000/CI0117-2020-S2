#include <iostream>
#include <string> 
#include <omp.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        cout << "Invalid number of parameters.\n";
        return 1;
    }

    double sum = 0.0;
    omp_set_num_threads(5);

    #pragma omp parallel 
    {
        int id = omp_get_thread_num();
        for (int i = id + 1; i < argc; i = i + 5){
            #pragma omp critical
            {
                sum += stoi(argv[i]);
            }
        }
    }

    cout << "Average: " << (sum / (argc - 1)) << endl;

    return 0;
}