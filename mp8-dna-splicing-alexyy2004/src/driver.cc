#include <iostream>
#include "dna_strand.hpp"

int main() {
    DNAstrand d1;
    d1.PushBack('a');
    d1.PushBack('b');
    d1.PushBack('c');
    d1.PushBack('d');
    d1.PushBack('e');

    d1.print();
    DNAstrand d2;
    d2.PushBack('s');
    d2.PushBack('s');
    d2.PushBack('s');

    d2.print();
    std::string temp = "e";
    d1.SpliceIn(temp.c_str(), d2);
    d1.print();
}