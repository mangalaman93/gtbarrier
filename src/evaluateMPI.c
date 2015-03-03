#include <stdio.h>
#include "mpi.h"
#include "disbarrier.c"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc,char **argv){
	if (argc != 2){ printf( "usage: %s barriers", argv[0] );}
	else{
	MPI_Init(NULL, NULL);
	int rank,j,diff,reps;
	reps=atoi(argv[1]);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        printf("Starting process %d\n",rank);
	struct timeval time1, time2;
        gettimeofday(&time1,NULL);
	for(j=0; j<reps; j++){
        disbarrier();
        }
        gettimeofday(&time2,NULL);
        diff=(time2.tv_sec-time1.tv_sec)*1000000 + time2.tv_usec-time1.tv_usec;
        printf("Time taken for %d pass %d barriers: %d\n",rank,reps,(int) diff);
	printf("Stopping...\n");
        disbarrier();
}
return 0;

}

