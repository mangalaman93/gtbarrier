#include <cstdio>
#include "timer.h"
using namespace std;

class TBarrierMP {
  int num_threads;
  int current_threads;

public:
  TBarrierMP(int n);
  ~TBarrierMP();
  void barrier();
};
