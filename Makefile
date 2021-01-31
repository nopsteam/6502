# A simple Makefile for compiling small SDL projects

SRCDIR := src
BINDIR := target
OBJDIR := $(BINDIR)/obj

# set the compiler
CC := clang

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

# header files
HDRS := $(wildcard $(SRCDIR)/*.h)

# source files
SRCS := $(wildcard $(SRCDIR)/*.c)

# generate names of object files
OBJS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.o))

# name of executable
EXEC := $(BINDIR)/6502

# default recipe
all: $(EXEC)

# make dirs if doesn't exists
$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(BINDIR)
	mkdir $(OBJDIR)

# recipe for building object files
$(OBJS): $(SRCS) $(HDRS) Makefile
	$(CC) -o $@ $(patsubst $(OBJDIR)/%,$(SRCDIR)/%,$(@:.o=.c)) -c $(CFLAGS)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -rf $(BINDIR)

.PHONY: all clean
