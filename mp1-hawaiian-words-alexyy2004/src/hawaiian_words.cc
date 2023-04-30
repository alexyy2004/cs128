#include <iostream>
#include <string>

#include "functions.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "ABABABA" << std::endl;
    return 1;
  }
  std::string word = argv[1];
  std::cout << HawaiianWord(word) << std::endl;
}