/*
 * OpenMP Barrier (Centralised Barrier)
 */

#include <cstdio>
#include <cmath>
#include <omp.h>
using namespace std;

class CBarrierMP {
  int num_threads;
  int count;

  // sense variables
  volatile bool *wakeup_sense;
  volatile bool global_wakeup;

public:
  CBarrierMP(int nthreads);
  ~CBarrierMP();
  void barrier();
};
