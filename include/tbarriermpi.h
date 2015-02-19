#include <cstdio>
#include <cmath>
using namespace std;

class TBarrierMPI {
  int num_threads;

public:
  TBarrierMPI(int nthreads);
  ~TBarrierMPI();
  void barrier(int thread_id);
};
