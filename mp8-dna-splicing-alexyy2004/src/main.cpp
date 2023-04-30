#include "dna_strand.hpp"
#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>

std::string randomDNA(int length) {
    static const std::string alphabet = "ACGT";
    std::default_random_engine generator(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<int> distribution(0, static_cast<int>(alphabet.size()) - 1);
    std::string result;
    
    for (int i = 0; i < length; i++) {
        result.push_back(alphabet[distribution(generator)]);
    }

    return result;
}

int main() {
    DNAstrand strand1;
    DNAstrand strand2;
    int i = 0;
    while (i < 10000) {
        std::cout << "Recursive log: "  << ++i << std::endl;
        strand1.~DNAstrand();
        strand2.~DNAstrand();
        std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(10, 50);
            int random_number = dis(gen);
        
        std::string dna = randomDNA(random_number);
        for (char c : dna) {
            strand1.PushBack(c);
        }
        std::cout << "Original Strand: ";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));  //防止电脑暴毙,可以自己调小
        strand1.print();
        std::string pattern = randomDNA(3);
        strand2.PushBack('S');
        strand2.PushBack('S');
        strand2.PushBack('S');
        strand1.SpliceIn(pattern.c_str(), strand2);
        std::cout << "Resulting Strand: ";
        std::this_thread::sleep_for(std::chrono::milliseconds(20));  //防止电脑暴毙
        strand1.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));  //防止电脑暴毙
        std::cout << std::endl;
    }

    return 0;
}
/*
 配件：自行加入DNAstrand.hpp
 
 void print() const {
       for (Node* p = head_; p != nullptr; p = p->next) {
           std::cout << p->data;
       }
       std::cout << '\n';
   }
 
 配件2: 加入cpp
 
 void DNAstrand::PushBack(char data) {
     Node* new_node = new Node(data);

     if (head_ == nullptr) {
         head_ = tail_ = new_node;
     } else {
         tail_->next = new_node;
         tail_ = new_node;
     }
 }
 
 */
