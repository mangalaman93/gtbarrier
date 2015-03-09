/*
 * as rank 0 is lagging behind, but still all process
 * output almost at the same time
*/

#include <unistd.h>
#include <cstdlib>
#include <mpi.h>
#include "tbarriermpi.h"
using namespace std;

int main() {
  int nprocs, rank;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  TBarrierMPI tbmpi(nprocs);
  tbmpi.barrier();

  printf("first hello from %d\n", rank);
  if(rank == 0)
    usleep(1000000);
  tbmpi.barrier();

  printf("second hello from %d\n", rank);
  if(rank == 0)
    usleep(1000000);
  tbmpi.barrier();

  printf("third hello from %d\n", rank);
  if(rank == 0)
    usleep(1000000);
  tbmpi.barrier();

  MPI_Finalize();
  return 0;
}
