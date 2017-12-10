# <N Queens Problem Solver - Genetic Algorithm> makefile

# define the C compiler to use
CC = gcc

# detect OS
UNAME := $(shell uname)

# define any compile-time flags depending on the OS
ifeq ($(UNAME), Linux)
	CFLAGS = -D LINUX -Ofast
endif
ifeq ($(UNAME), Darwin)
	CFLAGS = -D OSX -Ofast
endif

# define any directories containing header files other than /usr/include
INCLUDES = -I lib

# define custom library paths
LFLAGS = -L lib

# define any libraries to link into executable (only Linux needs this)
ifeq ($(UNAME), Linux)
	LFLAGS = -D LINUX -lm -lbsd
endif

# define the C source files
_SRCS1 = queens_GA.c genetics.c strategies.c utils.c arguments.c constants.c
_SRCS2 = queens_rand.c genetics.c utils.c constants.c arguments.c
_SRCS3 = allqueens_GA.c genetics.c utils.c arguments.c constants.c

# place them into the right repository folder
SDIR = src
SRCS1 = $(patsubst %,$(SDIR)/%,$(_SRCS1))
SRCS2 = $(patsubst %,$(SDIR)/%,$(_SRCS2))
SRCS3 = $(patsubst %,$(SDIR)/%,$(_SRCS3))

# define the executable files
P1 = queens_GA.out
P2 = queens_random.out
P3 = allqueens_GA.out

.PHONY: clean

# run the compiler
all: $(P1) $(P2) $(P3)
	@echo The executables \'$(P1)\', \'$(P2)\' and \'$(P3)\ have been compiled

$(P1):
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(P1) $(SRCS1) $(LFLAGS) $(LIBS)

$(P2):
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(P2) $(SRCS2) $(LFLAGS) $(LIBS)

$(P3):
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(P3) $(SRCS3) $(LFLAGS) $(LIBS)

# in case we want to delete the executables
clean:
	@$(RM) -r $(P1) $(P2) $(P3)
	@echo The executables \'$(P1)\', \'$(P2)\' and \'$(P3)\' have been deleted
