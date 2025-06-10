#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

/**
 * @file MyContainer.hpp
 * @brief Header-only template container with six custom iterator traversal orders.
 * @author
 *   <danieldaniel2468@gmail.com>
 */

#include <vector>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <numeric>

namespace ariel {

/**
 * @class MyContainer
 * @brief A generic container supporting six distinct iteration orders.
 *
 * @tparam T The type of elements stored; requires operator< and operator==.
 *
 * Features:
 *  - addElement() / removeElement()
 *  - size()
 *  - operator<< for streaming
 *  - Ascending, Descending, Side-Cross, Reverse, Insertion, Middle-Out iterators
 */
template<typename T>
class MyContainer {
private:
    std::vector<T> data;  ///< Underlying storage for elements.

public:
    /**
     * @brief Default constructor.
     */
    MyContainer() = default;

    /**
     * @brief Default destructor.
     */
    ~MyContainer() = default;

    /**
     * @brief Add an element to the container.
     * @param elem The element to add.
     */
    void addElement(const T& elem);

    /**
     * @brief Remove all occurrences of an element.
     * @param elem The element to remove.
     * @throws std::runtime_error if the element is not found.
     */
    void removeElement(const T& elem);

    /**
     * @brief Get the number of elements in the container.
     * @return Current size.
     */
    std::size_t size() const;

    /**
     * @brief Stream output operator.
     * @param os Output stream.
     * @param cont Container to print.
     * @return Reference to the stream.
     *
     * Prints elements in insertion order, e.g. "[ a b c ]".
     */
    friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& cont) {
        os << "[ ";
        for (const auto& e : cont.data) {
            os << e << " ";
        }
        return os << "]";
    }

    // Forward declarations of nested iterator types.
    class AscendingIterator;    ///< Iterates from smallest to largest.
    class DescendingIterator;   ///< Iterates from largest to smallest.
    class SideCrossIterator;    ///< Zig-zags: smallest, largest, 2nd smallest, 2nd largest, …
    class ReverseIterator;      ///< Iterates in reverse insertion order.
    class OrderIterator;        ///< Iterates in insertion order.
    class MiddleOutIterator;    ///< Starts at middle, then alternates left/right.

    /**
     * @brief Get iterator to beginning of ascending sequence.
     * @return AscendingIterator at first element.
     */
    AscendingIterator  begin_ascending_order() const;

    /**
     * @brief Get iterator to end of ascending sequence.
     * @return AscendingIterator one past last.
     */
    AscendingIterator  end_ascending_order()   const;

    /**
     * @brief Get iterator to beginning of descending sequence.
     * @return DescendingIterator at first element.
     */
    DescendingIterator begin_descending_order() const;

    /**
     * @brief Get iterator to end of descending sequence.
     * @return DescendingIterator one past last.
     */
    DescendingIterator end_descending_order()   const;

    /**
     * @brief Get iterator to beginning of side-cross sequence.
     * @return SideCrossIterator at first element.
     */
    SideCrossIterator  begin_side_cross_order() const;

    /**
     * @brief Get iterator to end of side-cross sequence.
     * @return SideCrossIterator one past last.
     */
    SideCrossIterator  end_side_cross_order()   const;

    /**
     * @brief Get iterator to beginning of reverse insertion sequence.
     * @return ReverseIterator at first element.
     */
    ReverseIterator    begin_reverse_order() const;

    /**
     * @brief Get iterator to end of reverse insertion sequence.
     * @return ReverseIterator one past last.
     */
    ReverseIterator    end_reverse_order()   const;

    /**
     * @brief Get iterator to beginning of insertion sequence.
     * @return OrderIterator at first element.
     */
    OrderIterator      begin_order() const;

    /**
     * @brief Get iterator to end of insertion sequence.
     * @return OrderIterator one past last.
     */
    OrderIterator      end_order()   const;

    /**
     * @brief Get iterator to beginning of middle-out sequence.
     * @return MiddleOutIterator at first element.
     */
    MiddleOutIterator  begin_middle_out_order() const;

    /**
     * @brief Get iterator to end of middle-out sequence.
     * @return MiddleOutIterator one past last.
     */
    MiddleOutIterator  end_middle_out_order()   const;
};

} // namespace ariel

#include "MyContainer.cpp"

#endif // MYCONTAINER_HPP
