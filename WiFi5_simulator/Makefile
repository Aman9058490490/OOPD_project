# Compiler and flags
CXX = g++
CXXFLAGS = -I ./include

# Source files
SRCS = main.cpp $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Targets
test: mainDebug mainOptimized

mainDebug: $(OBJS)
	$(CXX) -g -o $@ $^

mainOptimized: $(OBJS)
	$(CXX) -O3 -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o src/*.o mainDebug mainOptimized
