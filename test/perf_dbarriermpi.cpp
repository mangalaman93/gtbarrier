#include <cstdlib>
#include <cstdio>
#include <mpi.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "dbarriermpi.h"

#define NUM_BARRIERS 1000

int main() {
  int num_procs, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  DBarrierMPI dbmpi(num_procs);

  struct timeval time1, time2;
  gettimeofday(&time1, NULL);
  for(int j=0; j<NUM_BARRIERS; j++) {
    dbmpi.barrier();
  }
  gettimeofday(&time2,NULL);

  double diff = (time2.tv_sec-time1.tv_sec)*1000000 + time2.tv_usec-time1.tv_usec;
  printf("%d,%d,%f\n", rank, num_procs, (float)diff/NUM_BARRIERS);

  MPI_Finalize();
  return 0;
}
