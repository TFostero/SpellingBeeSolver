CXX=g++
CXXFLAGS=-g -Wall -std=c++11
TARGET=sbsolve

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET).exe $(TARGET).cpp  Node.cpp Trie.cpp

clean:
	rm -f $(TARGET)

