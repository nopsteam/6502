# C++ compiler
CXX     = g++

# C compiler
CC      = gcc

# C compilation flags
CFLAGS  = -std=c99 -Wall -pthread -DNDEBUG -O3

# Preprocessor definitions
C_DEFS  = -D_POSIX_C_SOURCE=199309

# Linker flags
LDFLAGS += -lz -lm -lgraph

# Build targets
all: program

# Rules for converting .c files into .o files
.SUFFIXES: .c

%.o: %.c
		$(CC) $(C_DEFS) $(CFLAGS) -MMD -c $<

# List of source files
SRCS  = main.c
		#SourceFile1.c \
		#SourceFile2.c \
		#SourceFile3.c \
		#main.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

# Include the .d dependency files
-include $(DEPS)

# Build the target "program"
program: $(OBJS)
		 $(CC) $(C_DEFS) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
		rm -f *.o *.d program

