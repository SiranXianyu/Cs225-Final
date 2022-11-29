EXENAME = main

CXX = clang++
CXXFLAGS = -std=c++11 -g -O0 -Wall -Wextra

all : $(EXENAME)

$(EXENAME): ./src/graph.o ./src/graph.h ./src/bfs.o ./src/bfs.hpp
 $(CXX) $(CXXFLAGS) main.cpp ./src/graph.o ./src/bfs.o  -o $(EXENAME)

graph.o: graph.h graph.cpp
 $(CXX) $(CXXFLAGS) -c ./src/graph.cpp

bfs.o: bfs.hpp
 $(CXX) $(CXXFLAGS) -c ./src/bfs.hpp

.PHONY: clean
clean:
 rm -f *.o $(EXENAME)




