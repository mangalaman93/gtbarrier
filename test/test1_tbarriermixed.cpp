/*
 * as rank 0 is lagging behind, but still all process
 * output almost at the same time
*/

#include <unistd.h>
#include <cstdlib>
#include "tbarriermixed.h"
using namespace std;

int main() {
  // openmpi processes
  int nnodes, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nnodes);

  // openmp threads
  omp_set_num_threads(8);

  // barrier constructor
  TBarrierMixed tbmixed(nnodes, 8);
  int tid;

  #pragma omp parallel shared(tbmixed) private(tid)
  {
    tid = omp_get_thread_num();
    tbmixed.barrier();

    printf("first hello from (%d,%d)\n", rank, tid);
    if(rank == 0 && tid == 0)
      usleep(1000000);
    tbmixed.barrier();

    printf("second hello from (%d,%d)\n", rank, tid);
    if(rank == 0 && tid == 0)
      usleep(1000000);
    tbmixed.barrier();

    printf("third hello from (%d,%d)\n", rank, tid);
    if(rank == 0 && tid == 0)
      usleep(1000000);
    tbmixed.barrier();
  }

  MPI_Finalize();
  return 0;
}
