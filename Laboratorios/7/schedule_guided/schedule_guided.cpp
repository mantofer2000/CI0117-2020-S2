#include <omp.h>
#include <bits/stdc++.h>

int main(){

    omp_set_num_threads(2);
    #pragma omp parallel for schedule(guided, 2)
    for(int i = 0; i < 20; i++){
        #pragma omp critical
        {
            std :: cout << "Thread num : " << omp_get_thread_num() << " has iteration : " << i << std :: endl; 
        }
    }

    return 0;
}