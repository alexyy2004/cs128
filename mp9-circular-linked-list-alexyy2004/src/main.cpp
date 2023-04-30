#include <iostream>
#include "circular-linked-list.hpp"

template <typename T>
void printList(const CircularLinkedList<T>& list) {
    std::cout << list << std::endl;
}

int main() {
    // Test 1: Copy constructor in Order::kASC
    CircularLinkedList<int> list1;
    list1.InsertInOrder(5);
    list1.InsertInOrder(3);
    list1.InsertInOrder(7);

    CircularLinkedList<int> list1_copy(list1);
    std::cout << "List1 (Original): ";
    printList(list1);
    std::cout << "List1 (Copy): ";
    printList(list1_copy);

    // Test 2: Copy constructor in Order::kDESC
    CircularLinkedList<int> list2;
    list2.InsertInOrder(5);
    list2.Reverse();
    list2.InsertInOrder(3);
    list2.InsertInOrder(7);

    CircularLinkedList<int> list2_copy(list2);
    std::cout << "List2 (Original): ";
    printList(list2);
    std::cout << "List2 (Copy): ";
    printList(list2_copy);

    // Test 3: Copy assignment operator in Order::kASC
    CircularLinkedList<int> list3;
    list3.InsertInOrder(10);
    list3.InsertInOrder(8);

    list3 = list1;
    std::cout << "List1 (Original): ";
    printList(list1);
    std::cout << "List3 (Assigned): ";
    printList(list3);

    // Test 4: Copy assignment operator in Order::kDESC
    CircularLinkedList<int> list4;
    list4.InsertInOrder(10);
    list4.Reverse();
    list4.InsertInOrder(12);

    list4 = list2;
    std::cout << "List2 (Original): ";
    printList(list2);
    std::cout << "List4 (Assigned): ";
    printList(list4);
    
    // Test 1: Copy constructor with empty list
        CircularLinkedList<int> empty_list;
        CircularLinkedList<int> copied_empty_list(empty_list);
        std::cout << "Test 1: Copy constructor with empty list:\n";
        std::cout << "Empty list: " << empty_list << "\n";
        std::cout << "Copied empty list: " << copied_empty_list << "\n\n";

        // Test 2: Copy constructor with non-empty list
        CircularLinkedList<int> original_list;
        original_list.InsertInOrder(3);
        original_list.InsertInOrder(1);
        original_list.InsertInOrder(2);
        CircularLinkedList<int> copied_list(original_list);
        std::cout << "Test 2: Copy constructor with non-empty list:\n";
        std::cout << "Original list: " << original_list << "\n";
        std::cout << "Copied list: " << copied_list << "\n\n";

        // Test 3: Assignment operator with empty list
        CircularLinkedList<int> assigned_empty_list;
        assigned_empty_list = empty_list;
        std::cout << "Test 3: Assignment operator with empty list:\n";
        std::cout << "Empty list: " << empty_list << "\n";
        std::cout << "Assigned empty list: " << assigned_empty_list << "\n\n";

        // Test 4: Assignment operator with non-empty list
        CircularLinkedList<int> assigned_list;
        assigned_list.InsertInOrder(6);
        assigned_list.InsertInOrder(5);
        assigned_list.InsertInOrder(4);
        assigned_list = original_list;
        std::cout << "Test 4: Assignment operator with non-empty list:\n";
        std::cout << "Original list: " << original_list << "\n";
        std::cout << "Assigned list: " << assigned_list << "\n\n";

        // Test 5: Destructor with empty list
        {
            CircularLinkedList<int> empty_list_to_destruct;
        }  // Destructor should be called when leaving this block

        // Test 6: Destructor with non-empty list
        {
            CircularLinkedList<int> list_to_destruct;
            list_to_destruct.InsertInOrder(9);
            list_to_destruct.InsertInOrder(8);
            list_to_destruct.InsertInOrder(7);
        }  // Destructor should be called when leaving this block
    
    // Test 1: Insert in ascending order
        CircularLinkedList<int> cll_asc;
        cll_asc.InsertInOrder(5);
        cll_asc.InsertInOrder(3);
        cll_asc.InsertInOrder(10);
        cll_asc.InsertInOrder(1);
        cll_asc.InsertInOrder(7);

        std::cout << "Test 1 - Ascending Order:\n";
        std::cout << cll_asc << std::endl;

        // Test 2: Insert in descending order
        CircularLinkedList<int> cll_desc;
        cll_desc.Reverse(); // Set node_order_ to kDESC
        cll_desc.InsertInOrder(5);
        cll_desc.InsertInOrder(3);
        cll_desc.InsertInOrder(10);
        cll_desc.InsertInOrder(1);
        cll_desc.InsertInOrder(7);

        std::cout << "Test 2 - Descending Order:\n";
        std::cout << cll_desc << std::endl;

        // Test 3: Insert duplicate values
        CircularLinkedList<int> cll_duplicate;
        cll_duplicate.InsertInOrder(5);
        cll_duplicate.InsertInOrder(3);
        cll_duplicate.InsertInOrder(10);
        cll_duplicate.InsertInOrder(3);
        cll_duplicate.InsertInOrder(7);
        cll_duplicate.InsertInOrder(5);

        std::cout << "Test 3 - Duplicate Values:\n";
        std::cout << cll_duplicate << std::endl;

    return 0;
}

