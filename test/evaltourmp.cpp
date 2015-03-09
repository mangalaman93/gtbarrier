#include <unistd.h>
#include <cstdlib>
#include <omp.h>
#include "tbarriermp.h"
using namespace std;

int NUM_THREADS=8;
int NUM_BARRIERS=8;

int main(int argc, char **argv) {
  if (argc != 3){ printf( "usage: %s num_barriers num_threads\n", argv[0] ); return -1;}
   NUM_BARRIERS=atoi(argv[1]);
   NUM_THREADS=atoi(argv[2]);

  omp_set_num_threads(NUM_THREADS);
  TBarrierMP tbmp(NUM_THREADS);
  int sum=0;

  #pragma omp parallel 
  { 
    int j;
    double time1, time2;
    time1 = omp_get_wtime();
    for(j=0; j<NUM_BARRIERS; j++){tbmp.barrier();}
    time2 = omp_get_wtime();
    #pragma omp critical
    {sum+=(time2-time1)*1000000;}
    tbmp.barrier();
  }
  printf("Average time per barrier: ,%d, us\n",(int)(sum/NUM_BARRIERS));
  return (int)(sum/NUM_BARRIERS);
}
