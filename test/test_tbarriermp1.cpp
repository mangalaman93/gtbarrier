#include <unistd.h>
#include <cstdlib>
#include <omp.h>
#include "tbarriermp.h"
using namespace std;

int main() {
  TBarrierMP tbmp(2);
  int a[2]={-1,-1};

#pragma omp parallel
  if(omp_get_thread_num() < 2) {
    a[omp_get_thread_num()] = omp_get_thread_num();
    usleep(rand()%1000000);
    printf("a[%d] = %d\n",omp_get_thread_num(), a[omp_get_thread_num()]);
  }

  tbmp.barrier();

#pragma omp parallel
  if(omp_get_thread_num() < 2) {
    a[omp_get_thread_num()] = -1;
    usleep(rand()%1000000);
    printf("a[%d] = %d\n",omp_get_thread_num(), a[omp_get_thread_num()]);
  }

  return 0;
}
