#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <omp.h>
#include <mpi.h>
#include "tbarriermixed.h"
using namespace std;

#define NUM_BARRIERS 1000

int main(int argc, char **argv) {
  // MP
  int num_threads = atoi(argv[1]);
  omp_set_num_threads(num_threads);

  int *sum = new int[num_threads];
  for(int i=0; i<num_threads; i++) {
    sum[i] = 0;
  }

  // MPI
  int num_procs, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Mixed barrier
  TBarrierMixed tbmixed(num_procs, num_threads);

  #pragma omp parallel shared(num_threads, tbmixed)
  {
    if(omp_get_num_threads() != num_threads) {
      printf("error occured\n");
      exit(1);
    }

    int tid = omp_get_thread_num();
    double time1, time2;
    time1 = omp_get_wtime();
    for(int j=0; j<NUM_BARRIERS; j++) {
      tbmixed.barrier();
    }
    time2 = omp_get_wtime();

    sum[tid] += (time2-time1)*1000000;
  }

  int s = 0;
  for(int i=0; i<num_threads; i++) {
    s += sum[i];
  }

  printf("%d,%d,%d,%f\n", rank, num_procs, num_threads, (float)s/num_procs/num_threads);

  delete[] sum;
  MPI_Finalize();
  return 0;
}
