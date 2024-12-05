# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -g

# Files
SRCS = $(wildcard *.cpp)

# Default target
EXE = $(SRCS:.cpp=)

# Default target
all: $(EXE)

# Rule to compile .cpp files to executables
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean up executables
clean:
	rm -f $(EXE)