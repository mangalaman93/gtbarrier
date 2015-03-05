OMPFLAGS = -fopenmp
OMPLIBS = -lgomp

CC = gcc
CPPFLAGS = -g -Wall
LDFLAGS = -g -Wall
LDLIBS = $(OMPLIBS)

MPICC = mpicc
MPICH = /home/ubuntu/openmpi-1.8.1/ompi
CFLAGS = -I$(MPICH)/include

all: disbarrier evaluateMPI centralized

centralized: centralized.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

disbarrier: disbarrier.c
	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

evaluateMPI: evaluateMPI.c
	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	rm -f *.o disbarrier evaluateMPI
