#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 8
#define NUM_BARRIERS 8

static void centralized_barrier( int *count, int *sense, int *local_sense ){
        *local_sense = ! *local_sense;
        #pragma omp critical
        {
                (*count)--;
        }
        if( *count == 0 ){
        *count = NUM_THREADS;
        *sense = *local_sense;
        }
        else {
        while( *sense != *local_sense ) {}
        }
}

int main(){
printf("Initializing...\n");
omp_set_num_threads( NUM_THREADS );
int sense = 1, count = NUM_THREADS;

#pragma omp parallel shared(sense, count)
{
    int num_threads = omp_get_num_threads();
    int thread_num = omp_get_thread_num();
    int local_sense = 1;
    long j;
    double time1, time2;


    for(j=0; j<NUM_BARRIERS; j++){
        time1 = omp_get_wtime();
        //Centralized barrier
        centralized_barrier(&count, &sense, &local_sense);
        time2 = omp_get_wtime();
        //Centralized barrier reached by all threads. Continue.
        printf("Thread %d of %d arrived at barrier %d in %f ms\n",
                                 thread_num, num_threads,(int)j,time2-time1);
        }

}
printf("Stopping...\n");
return 0;
}

