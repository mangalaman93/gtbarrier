#include <unistd.h>
#include <cstdlib>
#include <mpi.h>
#include "tbarriermpi.h"
using namespace std;

int main() {
  TBarrierMPI tbmpi(5);

  return 0;
}
