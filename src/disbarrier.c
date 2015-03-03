#include <stdio.h>
#include "mpi.h"

void disbarrier(int n)
{
  int rank,dst,src;
  int p=n;
  //Initialization
  MPI_Status mpi_result;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int array[20]={0};
  int count = 0;
  //round=len(p)-len(logp)
  int pow=1;
  int logp=p;
  int msg=0;
  count++;
  do{   
	dst=(rank+pow) % p;
	src=((rank-pow) % p);
        if (src<0) {src+=p;}
	MPI_Send(&count, 1, MPI_INT, dst, 0, MPI_COMM_WORLD);
        //printf("%d sent a message %d to %d\n",rank,count,dst);
	//fflush(stdout);
	MPI_Recv(&array[src], 1, MPI_INT, src,0, MPI_COMM_WORLD, &mpi_result);
        //array[src]=msg;
	//printf("%d received a message %d from %d\n",rank,msg,src);
        //fflush(stdout); 
	//while(array[src]<count);
  	logp=logp>>1;
  	pow=pow<<1;
  } while(logp>1);
  fflush(stdout);
}

int main(int argc, char **argv)
{
  //Initialization
  MPI_Init(NULL, NULL);
  int n,rank;
  MPI_Comm_size(MPI_COMM_WORLD, &n);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  disbarrier(n);
  printf("First hello from %d\n\n",rank);
  disbarrier(n);
  printf("Second hello from %d\n\n",rank);
  disbarrier(n);
  printf("Third hello from %d\n\n",rank);
  disbarrier(n);
  MPI_Finalize();
  return 0;
}

