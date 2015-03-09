/*
 * OpenMPI Barrier (Dissemination Barrier)
 */

#include <cstdio>
#include <cmath>
#include <mpi.h>
using namespace std;

class DBarrierMPI {
  int num_procs;

public:
  DBarrierMPI(int nporcs);
  ~DBarrierMPI();
  void barrier();
};
