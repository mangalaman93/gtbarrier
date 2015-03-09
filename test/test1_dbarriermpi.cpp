#include <unistd.h>
#include <cstdlib>
#include <mpi.h>
#include "dbarriermpi.h"
using namespace std;

int main() {
  int nprocs, rank;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  DBarrierMPI dbmpi(nprocs);
  dbmpi.barrier();

  printf("first hello from %d\n", rank);
  if(rank == 0)
    usleep(1000000);
  dbmpi.barrier();

  printf("second hello from %d\n", rank);
  if(rank == 0)
    usleep(1000000);
  dbmpi.barrier();

  printf("third hello from %d\n", rank);
  if(rank == 0)
    usleep(1000000);
  dbmpi.barrier();

  MPI_Finalize();
  return 0;
}
