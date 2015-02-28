#include "tbarriermpi.h"

TBarrierMPI::TBarrierMPI(int nprocs) {
  num_procs = nprocs;
}

TBarrierMPI::~TBarrierMPI() {
}

void TBarrierMPI::barrier() {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Parameters
  char msg='*';
  MPI_Status stat;

  /* barrier tree: left node of the tree always wins
   * i.e. out of P4, P6 => P4 wins */
  int temp_id = rank;
  int temp_procs = num_procs;
  int offset = 1;
  while(temp_procs != 1) {
    // if I am winner, spin on current barrier sense variable
    // if I am looser, reset current barrier sense & break
    if(temp_id%2 == 0) { // winner
      if(temp_id+1 < temp_procs) { // odd number of processes
        MPI_Recv(&msg, 1, MPI_CHAR, rank+offset, 1000+rank, MPI_COMM_WORLD, &stat);
      }
    } else { // looser
      int dest = rank-offset;
      MPI_Send(&msg, 1, MPI_CHAR, dest, 1000+dest, MPI_COMM_WORLD);
      break;
    }

    temp_id = temp_id/2;
    temp_procs = (temp_procs+1)/2;
    offset *= 2;
  }

  // wake up
  MPI_Bcast(&msg, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
}
