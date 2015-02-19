#include "tbarriermpi.h"

TBarrierMPI::TBarrierMPI(int nthreads) {
  num_threads = nthreads;
}

TBarrierMPI::~TBarrierMPI() {
}

void TBarrierMPI::barrier(int thread_id) {
}
