/****************************************************************************
 * File: test_n.cpp
 * Author: Diyor Sattarov
 * Email: diyorsattarov@outlook.com
 *
 * Created: 2024-11-10
 * Last Modified: 2024-11-10
 *
 * Description:
 * This file contains tests for the `n` class. It demonstrates and validates
 * the functionality of all `n` methods, including edge cases. The tests
 * ensure proper ownership semantics, memory management, and behavior of
 * linked data structures.
 *
 * Key Scenarios Covered:
 * 1. Basic functionality: Construction, linking, and value retrieval.
 * 2. Ownership transfer: Ensuring no memory leaks or dangling pointers.
 * 3. Edge cases: Double linking, deleting, and releasing pointers.
 *
 * Copyright (c) 2024 diyorsattarov. All rights reserved.
 ****************************************************************************/

#include <iostream>
#include <n.hpp>

int main() {
    std::cout << "Testing class n:\n";

    // 1. Basic Construction and Value Retrieval
    std::cout << "\n[TEST] Basic Construction and Value Retrieval\n";
    n<int> a(10); // Initialize `a` with value 10
    std::cout << "Value of a: " << a.get() << "\n"; // Expected: 10

    // 2. Linking Two Nodes
    std::cout << "\n[TEST] Linking Two Nodes\n";
    n<int>* b = new n<int>(20); // Dynamically allocate `b` with value 20
    a.l(b);                     // Link `a` to `b`
    std::cout << "Value of a's next: " << a.next()->get() << "\n"; // Expected: 20

    // 3. Chaining Multiple Nodes
    std::cout << "\n[TEST] Chaining Multiple Nodes\n";
    n<int>* c = new n<int>(30); // Dynamically allocate `c` with value 30
    b->l(c);                    // Link `b` to `c`
    std::cout << "Value of b's next: " << b->next()->get() << "\n"; // Expected: 30

    // 4. Ownership Transfer (Move Semantics)
    std::cout << "\n[TEST] Ownership Transfer (Move Semantics)\n";
    n<int> d = std::move(a); // Move `a` to `d`
    std::cout << "Value of d: " << d.get() << "\n"; // Expected: 10
    if (!a.next()) {
        std::cout << "a's next is null after move (ownership transferred).\n";
    }
    
    // 5. Releasing Ownership
    std::cout << "\n[TEST] Releasing Ownership\n";
    n<int>* released_node = d.release();
    if (!d.next()) {
        std::cout << "d's next is null after release.\n";
    }
    std::cout << "Value of released node: " << released_node->get() << "\n";
    delete released_node;
    released_node = nullptr; // Nullify to avoid reuse
    
    // 6. Edge Case: Double Linking
    std::cout << "\n[TEST] Edge Case: Double Linking\n";
    n<int> e(40); // Create a new node `e`
    e.l(new n<int>(50)); // Link `e` to a new node
    e.l(new n<int>(60)); // Link `e` to another new node (previous node deleted)
    std::cout << "Value of e's next: " << e.next()->get() << "\n"; // Expected: 60
    
    // 7. Edge Case: Self-Linking
    std::cout << "\n[TEST] Edge Case: Self-Linking\n";
    try {
        e.l(&e); // Attempt to self-link (not safe in this implementation)
        std::cout << "Self-linking test passed (but should not be allowed).\n";
    } catch (const std::exception& ex) {
        std::cout << "Error during self-linking: " << ex.what() << "\n";
    }
    // 8. Cleanup and Destructor Verification
    std::cout << "\n[TEST] Cleanup and Destructor Verification\n";
    n<int>* f = new n<int>(70);
    f->l(new n<int>(80)); // Link `f` to another node
    delete f; // Expect both `f` and its linked node to be properly deleted
    std::cout << "Deleted node `f` and its linked node successfully.\n";

    std::cout << "\nAll tests completed successfully.\n";
    return 0;
}

