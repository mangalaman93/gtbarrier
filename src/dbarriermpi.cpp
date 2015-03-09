#include "dbarriermpi.h"

DBarrierMPI::DBarrierMPI(int nprocs) {
  num_procs = nprocs;
}

DBarrierMPI::~DBarrierMPI() {}

void DBarrierMPI::barrier() {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  char msg='*';
  MPI_Status stat;

  for(int pow2=1; pow2<num_procs; pow2=pow2<<1) {
    int dst = (rank+pow2) % num_procs;
    int src = ((rank-pow2) % num_procs);
    if(src < 0) {
      src += num_procs;
    }
    MPI_Send(&msg, 1, MPI_CHAR, dst, 0, MPI_COMM_WORLD);
    MPI_Recv(&msg, 1, MPI_CHAR, src, 0, MPI_COMM_WORLD, &stat);
  }
}
