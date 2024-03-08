CXX=g++
CXXFLAGS=-g -Wall -std=c++11
TARGET=sbsolve

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -pthread -o $(TARGET).exe $(TARGET).cpp  Node.cpp Trie.cpp Checker.cpp Solver.cpp

clean:
	rm -f $(TARGET)

