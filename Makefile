# use -pg for profiling, use -g for debugging or replace
# it with `-ffast-math -O3` for enabling optimizations

CC = g++
DEBUG = -ffast-math -O3
PROFILE =
MPICC = /opt/intel/Compiler/11.1/059/bin/intel64/mpic++

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

#_MPMAIN = test1_tbarriermp evaltourmp defaultmp
_MPMAIN = evaltourmp defaultmp
MPMAIN = $(patsubst %,$(ODIR)/%,$(_MPMAIN))

_MPIOBJ = tbarriermpi.o
MPIOBJ = $(patsubst %,$(ODIR)/%,$(_MPIOBJ))

#_MPIMAIN = test1_tbarriermpi
_MPIMAIN = tourmpi defaultmpi
MPIMAIN = $(patsubst %,$(ODIR)/%,$(_MPIMAIN))

_MIXEDOBJ = tbarriermixed.o
MIXEDOBJ = $(patsubst %,$(ODIR)/%,$(_MIXEDOBJ))

_MIXEDMAIN = test1_tbarriermixed
MIXEDMAIN = $(patsubst %,$(ODIR)/%,$(_MIXEDMAIN))


all: dir $(MPMAIN) $(MPIMAIN) $(MIXEDMAIN)

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

$(ODIR)/%mixed.o: $(SDIR)/%mixed.cpp $(DEPS)
	$(MPICC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%mixed: $(TDIR)/%mixed.cpp $(OBJ) $(MIXEDOBJ)
	$(MPICC) $(CFLAGS) -o $@ $^ $(LIBS) $(MPIOBJ) -fopenmp

$(ODIR)/%r.o: $(SDIR)/%r.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%r: $(TDIR)/%r.cpp $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)


clean:
	rm -rf $(ODIR) *~

rebuild: clean all

.PHONY: clean
