CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/cord.cc ./includes/cord.hpp ./includes/shared_pointer.hpp ./src/cord_utilities.cc ./src/cord_utilities.cc
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/cord.cc ./src/cord_utilities.cc -o ./bin/exec

bin/tests: ./tests/tests.cc ./src/cord.cc ./includes/cord.hpp ./includes/shared_pointer.hpp ./src/cord_utilities.cc ./src/cord_utilities.cc
	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./src/cord.cc ./src/cord_utilities.cc -o ./bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* 
