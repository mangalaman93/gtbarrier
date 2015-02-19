# use -pg for profiling, use -g for debugging or replace
# it with `-ffast-math -O3` for enabling optimizations

CC = g++
DEBUG = -ffast-math -O3
PROFILE =
MPICC = mpic++

IDIR = include
SDIR = src
TDIR = test
ODIR = bin

CFLAGS = -I$(IDIR) $(DEBUG) $(PROFILE) -Wall
LIBS =

_DEPS = timer.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = timer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_MPOBJ = tbarriermp.o
MPOBJ = $(patsubst %,$(ODIR)/%,$(_MPOBJ))

_MPMAIN = test1_tbarriermp
MPMAIN = $(patsubst %,$(ODIR)/%,$(_MPMAIN))

_MPIOBJ = tbarriermpi.o
MPIOBJ = $(patsubst %,$(ODIR)/%,$(_MPIOBJ))

_MPIMAIN = test1_tbarriermpi
MPIMAIN = $(patsubst %,$(ODIR)/%,$(_MPIMAIN))

all: dir $(MPMAIN) $(MPIMAIN)

dir:
	mkdir -p $(ODIR)

$(ODIR)/%mpi.o: $(SDIR)/%mpi.cpp $(DEPS)
	$(MPICC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%mpi: $(TDIR)/%mpi.cpp $(OBJ) $(MPIOBJ)
	$(MPICC) $(CFLAGS) -o $@ $^ $(LIBS)

$(ODIR)/%mp.o: $(SDIR)/%mp.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%mp: $(TDIR)/%mp.cpp $(OBJ) $(MPOBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) -fopenmp

$(ODIR)/%r.o: $(SDIR)/%r.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%r: $(TDIR)/%r.cpp $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(ODIR) *~

rebuild: clean all

.PHONY: clean
