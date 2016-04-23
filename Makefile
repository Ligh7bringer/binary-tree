# compiler to use
CC = clang++

# flags
CFLAGS = -std=c++11

# executable
EXE = bintree

# header files
HDRS = binary_tree.h 

# source files
SRCS = binary_tree.cpp 

# object files
OBJS = $(SRCS:.c=.o)

# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
$(OBJS): $(HDRS) Makefile

# clean
clean:
	rm -f core $(EXE) *.o