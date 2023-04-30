#include <iostream>

#include "circular-linked-list.hpp"

template <typename T>
void printList(const CircularLinkedList<T>& list) {
    std::cout << list << std::endl;
}

int main() {
    CircularLinkedList<int> original_list;
        original_list.InsertInOrder(3);
        original_list.InsertInOrder(1);
        original_list.InsertInOrder(2);
        CircularLinkedList<int> copied_list(original_list);
        original_list.Reverse();
        std::cout << "Test 2: Copy constructor with non-empty list:\n";
        std::cout << "Original list: " << original_list << "\n";
        std::cout << "Copied list: " << copied_list << "\n\n";

    CircularLinkedList<int> assigned_list;
        assigned_list.InsertInOrder(6);
        assigned_list.InsertInOrder(5);
        assigned_list.InsertInOrder(4);
        assigned_list = original_list;
        std::cout << "Test 4: Assignment operator with non-empty list:\n";
        std::cout << "Original list: " << original_list << "\n";
        std::cout << "Assigned list: " << assigned_list << "\n\n";

}
