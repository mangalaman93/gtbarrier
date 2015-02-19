# use -pg for profiling, use -g for debugging or replace
# it with `-ffast-math -O3` for enabling optimizations

CC = g++
DEBUG = -ffast-math -O3
PROFILE =

IDIR = include
SDIR = src
TDIR = test
ODIR = bin

CFLAGS = -I$(IDIR) $(DEBUG) $(PROFILE) -Wall -fopenmp
LIBS = -lpthread

_DEPS = timer.h tbarriermp.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = timer.o tbarriermp.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_MAIN = test_tbarriermp1
MAIN = $(patsubst %,$(ODIR)/%,$(_MAIN))

all: dir $(MAIN)

dir:
	mkdir -p $(ODIR)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%: $(TDIR)/%.cpp $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(ODIR) *~

rebuild: clean all

.PHONY: clean
