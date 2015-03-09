#include <cstdlib>
#include <unistd.h>
#include <omp.h>
#include "tbarriermp.h"
using namespace std;

#define NUM_BARRIERS 10000

int main(int argc, char **argv) {
  int num_threads = atoi(argv[1]);
  printf("%d\n", num_threads);
  omp_set_num_threads(num_threads);

  int *sum = new int[num_threads];
  for(int i=0; i<num_threads; i++) {
    sum[i] = 0;
  }

  #pragma omp parallel shared(num_threads)
  {
    if(omp_get_num_threads() != num_threads) {
      printf("error occured\n");
      exit(1);
    }

    int tid = omp_get_thread_num();
    double time1, time2;
    time1 = omp_get_wtime();
    for(int j=0; j<NUM_BARRIERS; j++) {
      #pragma omp barrier
    }
    time2 = omp_get_wtime();

    sum[tid] += (time2-time1)*1000000;
  }

  int s = 0;
  for(int i=0; i<num_threads; i++) {
    printf("%d, %f\n", i, (float)sum[i]/NUM_BARRIERS);
    s += sum[i];
  }

  printf("avg, %f\n", (float)s/NUM_BARRIERS/num_threads);

  delete[] sum;
  return 0;
}
