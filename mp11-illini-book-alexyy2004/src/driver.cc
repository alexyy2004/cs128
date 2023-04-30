#include "illini_book.hpp"
#include <iostream>
int main() {
  const std::string& route_1 = "/home/vagrant/src/mp11-illini-book-alexyy2004/example/persons.csv";
  const std::string& route_2 = "/home/vagrant/src/mp11-illini-book-alexyy2004/example/relations.csv";
  IlliniBook ib(route_1, route_2);
  //ib.AreRelated(1,2);
  
  if (ib.AreRelated(9,1)) {
    std::cout << "related!" << std::endl;
  }
  std::cout << ib.CountGroups("128") << std::endl;
  std::vector<int> temp = ib.GetSteps(1,1);
  for (int i : temp) {
    std::cout << i << " ";
  }
}