#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'h', 'a', 'l', 'l', 'o'},
                                        {'q', 'a', 'l', 'e', 'o'},
                                        {'l', 'a', 'l', 'o', 'm'},
                                        {'l', 'l', 't', 'l', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'}};
  WordSearchSolver wss(puzzle);
  std::cout << wss.FindWord("hello", CheckDirection::kHorizontal);
  std::cout << wss.FindWord("essoo").char_positions.at(0);
}