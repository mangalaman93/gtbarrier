#include "cbarriermp.h"

CBarrierMP::CBarrierMP(int nthreads) {
  num_threads = nthreads;
  count = num_threads;

  // local sense variable
  wakeup_sense = new bool[nthreads];
  for(int i=0; i<nthreads; i++)
    wakeup_sense[i] = true;

  global_wakeup = false;
}

CBarrierMP::~CBarrierMP() {
  delete[] wakeup_sense;
}

void CBarrierMP::barrier() {
  int thread_id = omp_get_thread_num();

  // reverse wakeup sense
  wakeup_sense[thread_id] = !wakeup_sense[thread_id];

  // arrival
  #pragma omp critical
  {
    count--;
  }

  // wake up
  if(count == 0) {
    count = num_threads;
    global_wakeup = !global_wakeup;
  } else {
    while(wakeup_sense[thread_id] == global_wakeup);
  }
}
