#include <cstdio>
#include <cmath>
#include <omp.h>
using namespace std;

class TBarrierMP {
  int num_threads;
  int datasize;

  // sense variables
  volatile bool *barrier_sense;
  volatile bool *wakeup_sense;
  volatile bool global_wakeup;

public:
  TBarrierMP(int nthreads);
  ~TBarrierMP();
  void barrier();
};
