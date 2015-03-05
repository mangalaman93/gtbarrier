#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int NUM_THREADS=8;
int NUM_BARRIERS=8;

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

int main(int argc, char **argv){
        if (argc != 3){ printf( "usage: %s num_barriers num_threads\n", argv[0] ); return -1;}
        NUM_BARRIERS=atoi(argv[1]);
        NUM_THREADS=atoi(argv[2]);
        //printf("Initializing...\n");
        omp_set_num_threads( NUM_THREADS );
        int sense = 1, count = NUM_THREADS;
        int counter=0,sum=0;
        #pragma omp parallel shared(sense, count)
        {
            int local_sense = 1;
            long j;
            double time1, time2;
            time1 = omp_get_wtime();
            for(j=0; j<NUM_BARRIERS; j++){
                //Centralized barrier
                centralized_barrier(&count, &sense, &local_sense);
                //Centralized barrier reached by all threads. Continue.
             }
            time2 = omp_get_wtime();
        #pragma omp critical
        {
            sum+=(time2-time1)*1000;
            counter+=1;
        }

        }
        //printf("Average time per thread: %d ms\n",(int)(sum/(NUM_BARRIERS*NUM_THREADS)));
        //printf("Stopping...\n");
        printf("Average time per barrier: %d ms\n",(int)(sum/NUM_BARRIERS));
        return (int)(sum/NUM_BARRIERS);
}
