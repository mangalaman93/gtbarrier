#include <unistd.h>
#include <cstdlib>
#include "tbarriermixed.h"
#define MAXPROCESSORS 32

using namespace std;

int NUM_BARRIERS=8;
int NUM_THREADS=8;

int main(int argc, char **argv) {
  if (argc != 3){ printf( "usage: %s num_barriers num_threads\n", argv[0]);return-1;}
  NUM_BARRIERS=atoi(argv[1]);
  NUM_THREADS=atoi(argv[2]);

  // openmpi processes
  int n, rank, i;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &n);
  int sum=0;
  // openmp threads
  omp_set_num_threads(NUM_THREADS);

  // barrier constructor
  TBarrierMixed tbmixed(n,NUM_THREADS);

  #pragma omp parallel shared(tbmixed) private(tid)
  {
    double time1, time2;
    time1 = omp_get_wtime();
    for(i=0; i<NUM_BARRIERS; i++){tbmixed.barrier();}
    time2 = omp_get_wtime();
    #pragma omp critical
    {sum+=(time2-time1)*1000000;}
    tbmixed.barrier();

  }
  printf("Average time per barrier: %d ms(sync  %d nodes)\n",(int)(sum/NUM_BARRIERS),n);
  MPI_Finalize();
  return (int)(sum/NUM_BARRIERS);
}
