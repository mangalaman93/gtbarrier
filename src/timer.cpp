#include "timer.h"

void Timer::start() {
  is_running_ = 1;
  gettimeofday(&t_start_, NULL);
}

long double Timer::elapsed() {
  if(is_running_) {
    gettimeofday(&t_stop_, NULL);
  }

  return (long double)(t_stop_.tv_sec - t_start_.tv_sec)
    + (long double)(t_stop_.tv_usec - t_start_.tv_usec)*1e-6;
}

long double Timer::stop() {
  if(is_running_) {
    gettimeofday(&t_stop_, NULL);
    is_running_ = 0;
  }

  return elapsed();
}
