/*
 * Mixed Barrier Implementation: Tournament + Tournament
 */

#include <omp.h>
#include "tbarriermpi.h"
using namespace std;

class TBarrierMixed {
  int num_threads;
  int datasize;
  TBarrierMPI tmpi;

  // sense variables
  volatile bool *barrier_sense;
  volatile bool *wakeup_sense;
  volatile bool global_wakeup;

public:
  TBarrierMixed(int nnodes, int nthreads);
  ~TBarrierMixed();
  void barrier();
};
