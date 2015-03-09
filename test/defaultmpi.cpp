#include <unistd.h>
#include <cstdlib>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>
#define MAXPROCESSORS 32
using namespace std;

int NUM_BARRIERS=8;

int main(int argc, char **argv)
{
  if (argc != 2){ printf( "usage: %s num_barriers\n", argv[0]);return-1;}
  NUM_BARRIERS=atoi(argv[1]);
  //Initialization
  MPI_Init(NULL, NULL);
  int j,n,rank;
  double diff;
  int time[MAXPROCESSORS]={0};
  MPI_Comm_size(MPI_COMM_WORLD, &n);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  struct timeval time1, time2;
  gettimeofday(&time1,NULL);
  for(j=0; j<NUM_BARRIERS; j++){MPI_Barrier(MPI_COMM_WORLD);}
  gettimeofday(&time2,NULL);
  
  diff=(time2.tv_sec-time1.tv_sec)*1000 + time2.tv_usec/1000-time1.tv_usec/1000;
  time[n]=(int) diff/NUM_BARRIERS;
  
  printf("%d Average time %d processes took to sync per barrier:%d ms\n",rank,n,time[n]);
  
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}


