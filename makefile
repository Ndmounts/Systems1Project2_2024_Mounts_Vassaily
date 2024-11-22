# Makefile for Cache Simulation Project

# Compiler
CXX := g++

# Compiler Flags
CXXFLAGS := -Wall -Wextra -Werror -std=c++11 -g

# Directories (if you have separate directories, adjust accordingly)
INCLUDES := -I.

# Source Files
SRCS := \
    Memory.cc \
    AddressDecoder.cc \
    Block.cc \
    Set.cc \
    Cache.cc \
    Simulation.cc

# Object Files
OBJS := $(SRCS:.cc=.o)

# Executable Name
EXEC := Simulation

# Default Target
all: $(EXEC)

# Link Object Files to Create Executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Compile Memory.cc
Memory.o: Memory.cc Memory.h PerformanceCounter.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c Memory.cc

# Compile AddressDecoder.cc
AddressDecoder.o: AddressDecoder.cc AddressDecoder.h PerformanceCounter.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c AddressDecoder.cc

# Compile Block.cc
Block.o: Block.cc Block.h Memory.h PerformanceCounter.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c Block.cc

# Compile Set.cc
Set.o: Set.cc Set.h Block.h AddressDecoder.h Memory.h PerformanceCounter.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c Set.cc

# Compile Cache.cc
Cache.o: Cache.cc Cache.h Set.h AddressDecoder.h Memory.h PerformanceCounter.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c Cache.cc

# Compile Simulation.cc
Simulation.o: Simulation.cc Cache.h Set.h Block.h AddressDecoder.h Memory.h PerformanceCounter.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c Simulation.cc

# Clean Target to Remove Compiled Files
.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)
