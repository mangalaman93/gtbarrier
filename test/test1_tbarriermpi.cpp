#include <unistd.h>
#include <cstdlib>
#include <mpi.h>
#include "tbarriermpi.h"
using namespace std;

int main() {
  int nprocs, rank;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &nprocs);

  TBarrierMPI tbmpi(nprocs);
  tbmpi.barrier(rank);

  printf("first hello from %d\n", rank);
  if(rank == 0)
    usleep(1000000);
  tbmpi.barrier(rank);

  printf("second hello from %d\n", rank);
  if(rank == 0)
    usleep(1000000);
  tbmpi.barrier(rank);

  printf("third hello from %d\n", rank);
  if(rank == 0)
    usleep(1000000);
  tbmpi.barrier(rank);

  MPI_Finalize();
  return 0;
}
