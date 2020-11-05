/*                                                                                                                                                                            
  typedef enum omp_sched_t {                                                                                                                                                  
    omp_sched_static = 1,                                                                                                                                                     
    omp_sched_dynamic = 2,                                                                                                                                                    
    omp_sched_guided = 3,                                                                                                                                                     
    omp_sched_auto = 4                                                                                                                                                        
  } omp_sched_t;                                                                                                                                                              
*/

// preguntar por el static
#include <omp.h>
#include <stdio.h>
int main(void) {
  omp_sched_t kind;
  int chunk;
  omp_get_schedule(&kind, &chunk);
  printf("%d %d\n", kind, chunk);
}