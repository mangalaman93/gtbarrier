/*
 * all the output with `=>` prefix and without this prefix
 * should be together (cannot interleaved)
 */

#include <unistd.h>
#include <cstdlib>
#include <omp.h>
#include "tbarriermp.h"
using namespace std;

int main() {
  omp_set_num_threads(5);
  TBarrierMP tbmp(5);

  int nthreads, tid, i;
  float a[100], b[100], c[100];

  /* Some initializations */
  for (i=0; i<100; i++)
    a[i] = b[i] = i * 1.0;

  #pragma omp parallel shared(a,b,c,nthreads,tbmp) private(i,tid)
  {
    tid = omp_get_thread_num();
    if(tid == 0) {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);
    }
    printf("Thread %d starting...\n",tid);
    tbmp.barrier();

    #pragma omp for schedule(dynamic, 10) nowait
    for(i=0; i<100; i++) {
      c[i] = a[i] + b[i];
      printf("Thread %d: c[%d]= %f\n",tid,i,c[i]);
    }
    tbmp.barrier();

    #pragma omp for schedule(dynamic, 10) nowait
    for(i=0; i<100; i++) {
      c[i] = a[i] + b[i];
      printf("=> Thread %d: c[%d]= %f\n",tid,i,c[i]);
    }
    tbmp.barrier();
  }

  return 0;
}
