EXENAME = main

CXX = clang++
CXXFLAGS = -std=c++11 -g -O0 -Wall -Wextra

exec: src/graph.hpp main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

tests: src/graph.hpp tests/tests.cpp tests/catch.hpp
	$(CXX) $(CXXFLAGS) tests/tests.cpp -o tests/tests

.PHONY: clean exec tests
clean:
	rm -f *.o $(EXENAME)
