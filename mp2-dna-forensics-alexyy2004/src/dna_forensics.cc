#include <iostream>
#include <fstream>
#include <map>
#include "functions.hpp"
#include "utilities.hpp"
int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << argc << std::endl;
    return 1;
  }
  std::string file_name = argv[1];
  std::string dna = argv[2];

  //std::cout << dna << std::endl;

  std::ifstream ifs{file_name};
  std::vector<std::vector<std::string>> vec;
  for (std::string line; std::getline(ifs, line); line = "") {
    std::vector<std::string> temp = utilities::GetSubstrs(line, ',');
    vec.push_back(temp);
  }
  
  std::vector<std::string> dna_type = vec.at(0);
  auto temp = dna_type.begin();
  dna_type.erase(temp);
  std::vector<std::vector<std::string>> people;
  for (int i = 1; i < (int) vec.size(); ++i) {
    people.push_back(vec.at(i)); // {{Alex, "1", "2", "3"}}
  }
  
  /*
  for (std::string s : dna_type) {
    std::cout << s << std::endl;
  }
  for (std::vector<std::string> v : people) {
    for (std::string s : v) {
      std::cout << s <<std::endl;
    }
  }
  */
  
  
  std::cout << CheckDna(dna, dna_type, people) << std::endl;
  return 0;
}