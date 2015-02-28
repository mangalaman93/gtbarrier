#include "tbarriermixed.h"

TBarrierMixed::TBarrierMixed(int nnodes, int nthreads)
    : tmpi(nnodes) {
  num_threads = nthreads;

  int temp_threads = num_threads;
  datasize = 1;
  while(temp_threads != 1) {
    temp_threads = (temp_threads+1)/2;
    datasize += temp_threads;
  }
  barrier_sense = new bool[datasize];

  for(int i=0; i<datasize; i++) {
    barrier_sense[i] = true;
  }

  // local sense variable
  wakeup_sense = new bool[nthreads];
  for(int i=0; i<nthreads; i++)
    wakeup_sense[i] = true;

  global_wakeup = false;
}

TBarrierMixed::~TBarrierMixed() {
  delete[] barrier_sense;
  delete[] wakeup_sense;
}

void TBarrierMixed::barrier() {
  int thread_id = omp_get_thread_num();

  // reverse wakeup sense
  wakeup_sense[thread_id] = !wakeup_sense[thread_id];

  /* MP arrival tree: left node of the tree always wins
   * i.e. out of P4, P6 => P4 wins */
  int temp_id = thread_id;
  int base_index = 0;
  int temp_threads = num_threads;
  while(temp_threads != 1) {
    // if I am winner, spin on current barrier sense variable
    // if I am looser, reset current barrier sense & break
    if(temp_id%2 == 0) { // winner
      if(temp_id+1 < temp_threads) { // odd number of threads
        while(barrier_sense[base_index + temp_id/2]);
      }
    } else { // looser
      barrier_sense[base_index + temp_id/2] = false;
      break;
    }

    temp_id = temp_id/2;
    temp_threads = (temp_threads+1)/2;
    base_index += temp_threads;
  }

  // MPI arrival & wakeup
  if(thread_id == 0) {
    tmpi.barrier();
  }

  // MP wake up
  if(thread_id == 0) {
    for(int i=0; i<datasize; i++) {
      barrier_sense[i] = true;
    }

    global_wakeup = !global_wakeup;
  } else {
    while(wakeup_sense[thread_id] == global_wakeup);
  }
}
