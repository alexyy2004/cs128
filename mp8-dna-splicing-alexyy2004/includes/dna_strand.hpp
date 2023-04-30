#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP
#include <iostream>
#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  void PushBack(char data);
  
  void print() const {
      for (Node* p = head_; p != nullptr; p = p->next) {
          std::cout << p->data;
      }
      std::cout << '\n';
  }
  
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif