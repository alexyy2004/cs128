#include <iostream>

#include "db.hpp"
#include "db_table.hpp"

int main() {
  // write informal tests here
  DbTable table;
  //void** temp = new void*[1];
  //int value = 1;
  //temp[0] = &value;
  //table.rows_[(unsigned int)0] = temp;
  table.AddRow({"3.14", "1.13"});
  table.AddColumn({"GPA", DataType::kDouble});
}