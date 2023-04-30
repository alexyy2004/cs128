CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec

bin/exec: ./src/driver.cc ./includes/illini_book.hpp ./includes/utilities.hpp ./src/illini_book.cc ./src/utilities.cc
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/illini_book.cc ./src/utilities.cc -o ./bin/exec

.DEFAULT_GOAL := exec
.PHONY: clean exec

clean:
	rm -fr bin/* 
