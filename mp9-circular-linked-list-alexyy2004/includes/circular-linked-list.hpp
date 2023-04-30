#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source) {
    node_order_ = source.node_order_;
    if (source.head_ == nullptr && source.tail_ == nullptr) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      Node<T>* temp = source.head_;
      while (temp->next != source.head_) {
        InsertInOrder(temp->data);
        temp = temp->next;
        std::cout << temp->data << std::endl;
      }
      InsertInOrder(source.tail_->data);
    }
  }

  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source) {
    if (this == &source) {
      return *this;
    }
    Node<T>* node = head_;
    while (node != tail_) {
      Node<T>* next = node->next;
      delete node;
      node = next;
    }
    delete tail_;
    tail_ = nullptr;
    head_ = nullptr;

    if (node_order_ != source.node_order_) {
      if (node_order_ == Order::kASC) {
        node_order_ = Order::kDESC;
      } else {
        node_order_ = Order::kASC;
      }
    }
    if (source.head_ == nullptr && source.tail_ == nullptr) {
      tail_ = nullptr;
      head_ = nullptr;
    } else {
      Node<T>* temp = source.head_;
      while (temp->next != source.head_) {
        InsertInOrder(temp->data);
        temp = temp->next;
      }
      InsertInOrder(source.tail_->data);
      node_order_ = source.node_order_;
    }
    return *this;
  }

  ~CircularLinkedList() {
    Node<T>* node = head_;
    while (node != tail_) {
      Node<T>* next = node->next;
      delete node;
      node = next;
    }
    delete tail_;
    tail_ = nullptr;
    head_ = nullptr;
    node_order_ = Order::kASC;
  }

  void InsertInOrder(const T& data) {
    Node<T>* temp = head_;
    bool flag = true; // true: haven't inserted yet; false: have already inserted new_node
    if (temp == nullptr) {head_ = tail_ = new Node(data);head_->next = tail_;tail_->next = head_;
    } else {
      if (node_order_ == Order::kASC) {
        while (temp->next != head_) {
          if (flag && temp->data <= data && temp->next->data >= data) {Node<T>* next = temp->next;Node<T>* new_node = new Node(data, next);temp->next = new_node;flag = false;
          } else {temp = temp->next;}}
        if (flag) {
            if (data <= head_->data) {Node<T>* new_node = new Node(data, head_);tail_->next = new_node;head_ = new_node;
            } else {Node<T>* new_node = new Node(data, head_);tail_->next = new_node;tail_  = new_node;flag = false;
            }
        }
      } else {
        while (temp->next != head_) {
          if (flag && temp->data >= data && temp->next->data <= data) {
            Node<T>* next = temp->next;
            Node<T>* new_node = new Node(data, next);
            temp->next = new_node;
            flag = false;
          } else {
            temp = temp->next;
          }
        }
        if (flag) {
          if (data >= head_->data) {
            Node<T>* new_node = new Node(data, head_);
            tail_->next = new_node;
            head_ = new_node;
          } else {
            Node<T>* new_node = new Node(data, head_);
            tail_->next = new_node;
            tail_  = new_node;
            flag = false;
          }
        }
      }
    }
  }
  void Reverse() {
    if (head_ == nullptr && tail_ == nullptr) {
      if (node_order_ == Order::kASC) {
        node_order_ = Order::kDESC;
      } else {
        node_order_ = Order::kASC;
      }
    } else {
      Node<T>* previous = head_;
      Node<T>* current = nullptr;
      Node<T>* next = nullptr;
      Node<T>* cur_next = nullptr;
      while (current != head_) {
        current = previous->next;
        next = current->next;
        previous->next = cur_next;
        cur_next = previous;
        previous = current;
      }
      head_->next = tail_;
      Node<T>* temp = tail_;
      tail_ = head_;
      head_ = temp;
      if (node_order_ == Order::kASC) {
        node_order_ = Order::kDESC;
      } else {
        node_order_ = Order::kASC;
      }
    }
  }

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif