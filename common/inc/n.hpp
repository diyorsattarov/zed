/****************************************************************************
 * File: n.h
 * Author: Diyor Sattarov
 * Email: diyorsattarov@outlook.com
 *
 * Created: 2024-10-05
 * Last Modified: 2024-11-10
 *
 * Description: This header file defines a templated class `n` for linked data
 * structures. Ownership semantics are implemented to manage `nx_`.
 * Copyright (c) 2024 diyorsattarov. All rights reserved.
 ****************************************************************************/

#ifndef n_hpp
#define n_hpp

#include <iostream>

template <typename T>
class n {
public:
    T v_;        // Value stored in the n
    n* nx_;      // Pointer to the next n in the sequence (owned by this `n`)

    /**
     * @brief Constructs a new `n` with the given value.
     * @param v The value to store in the `n`.
     * @post The `n` is initialized with the given value and a null next pointer.
     */
    explicit n(const T& v) : v_(v), nx_(nullptr) {}

    /**
     * @brief Default constructor for the `n`.
     */
    n() : nx_(nullptr) {}

    /**
     * @brief Destructor to clean up the owned next `n`.
     */
    ~n() {
        if (nx_) {
            std::cout << "Deleting node with value: " << nx_->get() << "\n";
            delete nx_;
            nx_ = nullptr; // Nullify after deletion
        }
    }

    /**
     * @brief Links this `n` to another `n`, transferring ownership.
     * @param ne Pointer to the `n` that should follow this one.
     * @post Ownership of the provided `n` is transferred to this `n`.
     */
    void l(n* ne) {
        if (ne == this) { // Prevent self-linking
            throw std::runtime_error("Self-linking is not allowed");
        }
        if (nx_ != ne) { // Prevent double deletion if the same node is linked again
            delete nx_;
        }
        nx_ = ne;
    }

    /**
     * @brief Retrieves the value stored in this `n`.
     * @return The value of type `T` stored in the `n`.
     */
    T get() const { return v_; }

    /**
     * @brief Retrieves the pointer to the next `n`.
     * @return Pointer to the next `n` in the sequence.
     */
    n* next() const { return nx_; }

    /**
     * @brief Transfers ownership of the next `n` to the caller.
     * @return A pointer to the next `n`, with ownership transferred.
     * @post The `nx_` pointer is set to null.
     */
    n* release() {
        n* temp = nx_;
        nx_ = nullptr; // Nullify ownership in the current instance
        return temp;
    }

    /**
     * @brief Move constructor for ownership transfer.
     */
    n(n&& other) noexcept : v_(other.v_), nx_(other.nx_) {
        other.nx_ = nullptr; // Clear the source's pointer.
    }

    /**
     * @brief Move assignment operator for ownership transfer.
     */
    n& operator=(n&& other) noexcept {
        if (this != &other) {
            delete nx_; // Clean up existing resources.
            v_ = other.v_;
            nx_ = other.nx_;
            other.nx_ = nullptr; // Clear the source's pointer.
        }
        return *this;
    }

    /**
     * @brief Copy constructor is deleted to prevent unintended ownership duplication.
     */
    n(const n&) = delete;

    /**
     * @brief Copy assignment operator is deleted to prevent unintended ownership duplication.
     */
    n& operator=(const n&) = delete;
};

#endif // n_hpp

