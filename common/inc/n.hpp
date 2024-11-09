/****************************************************************************
 * File: n.h
 * Author: Diyor Sattarov
 * Email: diyorsattarov@outlook.com
 *
 * Created: 2024-10-05
 * Last Modified: 2024-10-09
 *
 * Description: This header file defines a templated class `n` for linked data
 * structures. Each `n` object contains a value of generic type `T` and a 
 * pointer to the next `n` object.
 * Copyright (c) 2024 diyorsattarov. All rights reserved.
 ****************************************************************************/

#ifndef n_hpp
#define n_hpp

#define nullptr 0

template <typename T>
class n {
    public:
        T v_;             // Value stored in the n
        n* nx_;           // Pointer to the next n in the sequence

        /**
         * @brief Constructs a new `n` with the given value
         * @param v The value to store in the `n`
         * @post The `n` is initialized with the given value and a null next pointer
         */
        n(const T& v) : v_(v), nx_(nullptr) {}

        /**
         * @brief Default constructor for the `n`
         */
        n() = default;

        /**
         * @brief Links this `n` to another `n`
         * @param ne Pointer to the `n` that should follow this one
         * @post The next pointer is set to the provided `n`
         */
        void l(n* ne) { nx_ = ne; }

        /**
         * @brief Retrieves the value stored in this `n`
         * @return The value of type `T` stored in the `n`
         */
        T get() const { return v_; }

        /**
         * @brief Retrieves the pointer to the next `n`
         * @return Pointer to the next `n` in the sequence
         */
        n* next() const { return nx_; }
};

#endif // n_hpp

