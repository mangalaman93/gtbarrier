#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#define MAXPROCESSORS 32

int NUM_BARRIERS=8;

void disbarrier(rank,n)
{
  int dst,src;
  //Initialization
  MPI_Status mpi_result;
  int array[MAXPROCESSORS]={0};
  int count = 1;
  //round=len(p)-len(logp)
  int pow=1;
  while(pow<n){   
	dst=(rank+pow) % n;
	src=((rank-pow) % n);
        if (src<0) {src+=n;}
	MPI_Send(&count, 1, MPI_INT, dst, 0, MPI_COMM_WORLD);
	//printf("%d, sent msg to %d, waiting on %d\n",rank,dst,src);
	MPI_Recv(&array[src], 1, MPI_INT, src,0, MPI_COMM_WORLD, &mpi_result);
  	pow=pow<<1;
  } 
  fflush(stdout);
}

int main(int argc, char **argv)
{
  if (argc != 3){ printf( "usage: %s num_barriers num_threads\n", argv[0]);return-1;}
  NUM_BARRIERS=atoi(argv[1]);
  //Initialization
  MPI_Init(NULL, NULL);
  int j,n,rank;
  double diff;
  int time[MAXPROCESSORS]={0};
  MPI_Comm_size(MPI_COMM_WORLD, &n);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  struct timeval time1, time2;
  //printf("Starting");
  fflush(stdout);
  gettimeofday(&time1,NULL);
  for(j=0; j<NUM_BARRIERS; j++){disbarrier(rank,n);}
  gettimeofday(&time2,NULL);
  diff=(time2.tv_sec-time1.tv_sec)*1000 + time2.tv_usec/1000-time1.tv_usec/1000;
  time[n]=(int) diff/NUM_BARRIERS;
  printf("%d Average time %d processes took to sync per barrier:%d ms\n",rank,n,time[n]);
  disbarrier(rank,n);
  //MPI_Bcast(&time[n], 1, MPI_INT,0, MPI_COMM_WORLD);
  //disbarrier(rank,n);
  //if (rank==0){
  //int sum=0;
  //for(j=0;j<n;j++){sum+=time[j];}
  //printf("%d :Average time per barrier:%d ms\n",rank,sum/n);}
  //disbarrier(rank,n);
  MPI_Finalize();
  return 0;
}

