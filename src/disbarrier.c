#include <stdio.h>
#include "mpi.h"
#define MAXPROCESSORS 20

void disbarrier()
{
  int n,rank,dst,src;
  //Initialization
  MPI_Comm_size(MPI_COMM_WORLD, &n);
  MPI_Status mpi_result;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int array[MAXPROCESSORS]={0};
  int count = 0;
  //round=len(p)-len(logp)
  int pow=1;
  int logp=n;
  count++;
  do{   
	dst=(rank+pow) % n;
	src=((rank-pow) % n);
        if (src<0) {src+=n;}
	MPI_Send(&count, 1, MPI_INT, dst, 0, MPI_COMM_WORLD);
	MPI_Recv(&array[src], 1, MPI_INT, src,0, MPI_COMM_WORLD, &mpi_result);
  	logp=logp>>1;
  	pow=pow<<1;
  } while(logp>0);
  fflush(stdout);
}

/*int main(int argc, char **argv)
{
  //Initialization
  MPI_Init(NULL, NULL);
  int n,rank;
  MPI_Comm_size(MPI_COMM_WORLD, &n);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  disbarrier();
  printf("First hello from %d\n\n",rank);
  disbarrier();
  printf("Second hello from %d\n\n",rank);
  disbarrier();
  printf("Third hello from %d\n\n",rank);
  disbarrier();
  MPI_Finalize();
  return 0;
}*/

