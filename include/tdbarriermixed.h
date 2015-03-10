/*
 * Mixed Barrier Implementation: Tournament + Tournament
 */

#include <omp.h>
#include "dbarriermpi.h"
using namespace std;

class TDBarrierMixed {
  int num_threads;
  int datasize;
  DBarrierMPI tmpi;

  // sense variables
  volatile bool *barrier_sense;
  volatile bool *wakeup_sense;
  volatile bool global_wakeup;

public:
  TDBarrierMixed(int nnodes, int nthreads);
  ~TDBarrierMixed();
  void barrier();
};
