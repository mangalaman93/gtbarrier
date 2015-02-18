#include <cstdio>
#include <cstdlib>
#include <sys/time.h>

class Timer {
  struct timeval t_start_;
  struct timeval t_stop_;
  int is_running_;

public:
  Timer() {}
  ~Timer() {}
  void start();
  long double elapsed();
  long double stop();
};
