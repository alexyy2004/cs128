#ifndef CORD_HPP
#define CORD_HPP

#include <string_view>
#include <iostream>
#include "shared_pointer.hpp"

class Cord {
public:
  Cord(std::string_view sv) {
    if (sv.empty()) {
      throw std::invalid_argument("aaa");
    }
    char* new_data = new char[sv.size() + 1];
    for (unsigned int i = 0; i < sv.size(); i++) {
      new_data[i] = sv[i];
    }
    new_data[sv.size()] = '\0';
    data_ = new_data;
    left_ = nullptr;
    right_ = nullptr;
    length_ = sv.size();
  }

  ~Cord() {
    delete[] data_;
    data_ = nullptr;
  }
  SharedPointer<char> ToString() const {
    int count = 0;
    char* str = new char[length_ + 1];
    RecurTostring(this, str, count);
    str[length_] = '\0';
    for (int i = 0; i < (int)(length_+1); i++) {
      std::cout << str[i] << std::endl;
    }
    SharedPointer<char> result = SharedPointer<char>(str, kSharedPointerType::kArray);
    return result;
  }

  void RecurTostring(const Cord* cord, char* str, int& count) const{
    if (cord->data_ == nullptr) {
      auto left = cord->left_;
      RecurTostring(left.Get(), str, count);
      auto right = cord->right_;
      RecurTostring(right.Get(), str, count);
    } else {
      for (int i = 0; i < (int)cord->length_; i++) {
        str[count] = cord->data_[i];
        count += 1;
      }
    }
  }
  // Provided, do not modify!
  Cord() = default;
  Cord(const Cord& rhs) = delete;
  Cord& operator=(const Cord& rhs) = delete;
  unsigned int Length() const { return length_; }
  const SharedPointer<Cord> Left() const { return left_; }
  const SharedPointer<Cord> Right() const { return right_; }
  const std::string_view Data() const { return data_; }

private:
  // data members
  SharedPointer<Cord> left_;
  SharedPointer<Cord> right_;
  char* data_ = nullptr;
  unsigned int length_ = 0;
  
  // friend functions
  friend SharedPointer<Cord> ConcatCords(const SharedPointer<Cord>& left_cord,
                                         const SharedPointer<Cord>& right_cord);
};

#endif