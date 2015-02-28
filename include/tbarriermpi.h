#include <cstdio>
#include <cmath>
#include <mpi.h>
using namespace std;

class TBarrierMPI {
  int num_procs;

public:
  TBarrierMPI(int nporcs);
  ~TBarrierMPI();
  void barrier();
};
