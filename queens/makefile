# Source: https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html

# This is an easier to use and modify makefile, but it is slightly more difficult to read than the simple one:
#
# 'make depend' uses makedepend to automatically generate dependencies
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc

# detect OS
UNAME := $(shell uname)

#define any compile-time flags
ifeq ($(UNAME), Linux)
	CFLAGS = -D LINUX
endif
ifeq ($(UNAME), Darwin)
	CFLAGS = -D OSX
endif

# define any directories containing header files other than /usr/include
INCLUDES = -I lib

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
#   option, something like (this will link in libmylib.so and libm.so:
ifeq ($(UNAME), Linux)
	LFLAGS = -D LINUX -lm -lbsd
endif

# define the C source files
_SRCS1 = queens_GA.c genetics.c strategies.c utils.c arguments.c constants.c
_SRCS2 = queens_rand.c genetics.c utils.c constants.c
#SRCS = src/queens_GA.c src/constants.c src/genetics.c src/utils.c src/arguments.c src/strategies.c

# define the C object files
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
SDIR = src
SRCS1 = $(patsubst %,$(SDIR)/%,$(_SRCS1))
SRCS2 = $(patsubst %,$(SDIR)/%,$(_SRCS2))

# define the executable file
P1 = queens_GA.out
P2 = queens_random.out

.PHONY: directories clean

all: $(P1) $(P2)
	@echo The executables \'$(P1)\' and \'$(P2)\' have been compiled

$(P1):
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(P1) $(SRCS1) $(LFLAGS) $(LIBS)

$(P2):
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(P2) $(SRCS2) $(LFLAGS) $(LIBS)

clean:
	@$(RM) -r $(P1) $(P2)
	@echo The executables \'$(P1)\' and \'$(P2)\' have been deleted

# DO NOT DELETE THIS LINE -- make depend needs it
