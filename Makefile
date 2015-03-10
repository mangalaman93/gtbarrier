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

_MPOBJ = tbarriermp.o cbarriermp.o
MPOBJ = $(patsubst %,$(ODIR)/%,$(_MPOBJ))

_MPMAIN = test1_tbarriermp test1_cbarriermp perf_defaultmp perf_tbarriermp perf_cbarriermp
MPMAIN = $(patsubst %,$(ODIR)/%,$(_MPMAIN))

_MPIOBJ = tbarriermpi.o dbarriermpi.o
MPIOBJ = $(patsubst %,$(ODIR)/%,$(_MPIOBJ))

_MPIMAIN = test1_tbarriermpi test1_dbarriermpi perf_defaultmpi perf_tbarriermpi perf_dbarriermpi
MPIMAIN = $(patsubst %,$(ODIR)/%,$(_MPIMAIN))

_MIXEDOBJ = tbarriermixed.o tdbarriermixed.o
MIXEDOBJ = $(patsubst %,$(ODIR)/%,$(_MIXEDOBJ))

_MIXEDMAIN = test1_tbarriermixed test1_tdbarriermixed perf_tdbarriermixed perf_tdbarriermixed
MIXEDMAIN = $(patsubst %,$(ODIR)/%,$(_MIXEDMAIN))

all: dir $(MPMAIN) $(MPIMAIN) $(MIXEDMAIN)

dir:
	mkdir -p $(ODIR)

$(ODIR)/%mpi.o: $(SDIR)/%mpi.cpp $(DEPS)
	$(MPICC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%mpi: $(TDIR)/%mpi.cpp $(OBJ) $(MPIOBJ)
	$(MPICC) $(CFLAGS) -o $@ $^ $(LIBS)

$(ODIR)/%mp.o: $(SDIR)/%mp.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< -fopenmp

$(ODIR)/%mp: $(TDIR)/%mp.cpp $(OBJ) $(MPOBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) -fopenmp

$(ODIR)/%mixed.o: $(SDIR)/%mixed.cpp $(DEPS)
	$(MPICC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%mixed: $(TDIR)/%mixed.cpp $(OBJ) $(MIXEDOBJ)
	$(MPICC) $(CFLAGS) -o $@ $^ $(LIBS) $(MPIOBJ) -fopenmp

clean:
	rm -rf $(ODIR) *~

rebuild: clean all

.PHONY: clean
