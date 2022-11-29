EXENAME = main

CXX = clang++
CXXFLAGS = -std=c++11 -g -O0 -Wall -Wextra

all : $(EXENAME)

$(EXENAME):./src/graph.o ./src/graph.h 
	$(CXX) $(CXXFLAGS) main.cpp ./src/graph.o  -o $(EXENAME)

graph.o: graph.h graph.cpp
	$(CXX) $(CXXFLAGS) -c ./src/graph.cpp


.PHONY: clean
clean:
	rm -f *.o $(EXENAME)



