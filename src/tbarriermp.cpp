#include "tbarriermp.h"

TBarrierMP::TBarrierMP(int n) {
  num_threads = n;
  current_threads = n;
}

TBarrierMP::~TBarrierMP() {
}

void TBarrierMP::barrier() {
  current_threads--;
  if(current_threads == 0) {
    current_threads = num_threads;
  }

  while(current_threads == num_threads);
}
