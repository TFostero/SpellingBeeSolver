CXX = g++
CXXFLAGS = -g -Wall -pthread -std=c++11 
SRCS = sbsolve.cpp Solver.cpp Trie.cpp Node.cpp ui.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = sbsolve.exe

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

