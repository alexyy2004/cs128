#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::~DNAstrand() {
    while (head_ != nullptr) {
        Node* next = head_->next;
        delete head_;
        head_ = next;
    }
}

void DNAstrand::PushBack(char data) {
     Node* new_node = new Node(data);
     if (head_ == nullptr) {
         head_ = tail_ = new_node;
     } else {
         tail_->next = new_node;
         tail_ = new_node;
     }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
    if (pattern[0] == '\0' || to_splice_in.head_ == nullptr) {
        throw std::invalid_argument("aaa");
    }
    if (&to_splice_in == this) {
        return;
    }
    //find the start point of the last appearance of pattern in sequence
    Node* cur_node = head_;
    int start_point = -1;
    int end_point = -1;
    int count = 0;
    while (cur_node != nullptr) {
        if (cur_node->data == pattern[0]) {
            int last_start_point = start_point;
            start_point = count;
            bool flag = true; // true: pattern matches; false: pattern doesn't match
            Node* temp = cur_node;
            for (unsigned int i = 1; pattern[i] != '\0'; ++i) {
                temp = temp->next;
                count += 1;
                if (temp == nullptr || temp->data != pattern[i]) {
                    flag = false;
                    count = start_point;
                    break;
                }
            }
            if (!flag) {
                start_point = last_start_point;
                cur_node = cur_node->next;
            } else {
                end_point = count;
                cur_node = temp;
                cur_node = cur_node->next;
            }
        } else {
            cur_node = cur_node->next;
        }
        count += 1;
    }
    //throw exception if no match pattern in sequence
    if (start_point == -1) {
        throw std::invalid_argument("aaa");
    }
    //destroy pattern in sequence
    Node* memory_part = head_;
    int num = 0;
    while (memory_part != nullptr) {
        if (num >= start_point && num <= end_point) {
            Node* next = memory_part->next;
            memory_part = nullptr;
            memory_part = next;
            num += 1;
        } else {
            memory_part = memory_part->next;
            num += 1;
        }
    }
    Node* node = head_;
    Node* before_pattern = nullptr;
    int index = 0;
    if (start_point == 0) {
        for (int i = 0; i <= end_point - start_point; i++) {
            Node* next = node->next;
            delete node;
            node = next;
        }
        head_ = node;
    } else {
        while (index < start_point - 1) {
            node = node->next;
            index += 1;
        }
        before_pattern = node;
        node = node->next;
        for (int i = 0; i <= end_point - start_point; i++) {
            Node* next = node->next;
            delete node;
            node = next;
        }
        before_pattern->next = node;
    }
    //insert new pattern
    int insert_index = 0;
    Node* current = head_;
    Node* next = nullptr;
    bool flag = true;
    while (flag) {
        if (start_point == 0) {
            Node* temp = head_;
            head_ = to_splice_in.head_;
            to_splice_in.tail_->next = temp;
            flag = false;
        } else {
            if (insert_index == start_point - 1) {
                next = current->next;
                current->next = to_splice_in.head_;
                to_splice_in.tail_->next = next;
                flag = false;
            } else {
                current = current->next;
                insert_index += 1;
            }
        }
    }
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr;
}