CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/draw.cpp ./src/graph.cpp ./src/BFS.cpp ./src/brandes.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests: ./tests/tests.cpp obj/catch.o ./src/draw.cpp ./src/graph.cpp ./src/BFS.cpp ./src/brandes.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@



.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*




