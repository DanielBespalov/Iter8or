#include "MyContainer.hpp"
#include <algorithm>
#include <numeric>
#include <stdexcept>

/**
 * danieldaniel2468@gmail.com
 */

namespace ariel {

// — Core operations —
// Adds an element at the end.
template<typename T>
void MyContainer<T>::addElement(const T& elem) {
    data.push_back(elem);
}

// Removes all occurrences of elem, throws if not found.
template<typename T>
void MyContainer<T>::removeElement(const T& elem) {
    if (std::count(data.begin(), data.end(), elem) == 0) {
        throw std::runtime_error("Element not found");
    }
    data.erase(std::remove(data.begin(), data.end(), elem), data.end());
}

// Returns number of stored elements.
template<typename T>
std::size_t MyContainer<T>::size() const {
    return data.size();
}

// — AscendingIterator —
// Iterates elements in increasing order.
template<typename T>
class MyContainer<T>::AscendingIterator {
    const MyContainer* cont;
    std::vector<std::size_t> order;
    std::size_t index;

    // Build sorted index map.
    void initOrder() {
        order.resize(cont->data.size());
        std::iota(order.begin(), order.end(), 0);
        std::sort(order.begin(), order.end(),
                  [&](auto a, auto b){ return cont->data[a] < cont->data[b]; });
    }

public:
    AscendingIterator(const MyContainer* c, std::size_t i)
        : cont(c), index(i) { initOrder(); }

    AscendingIterator& operator++() { ++index; return *this; }
    bool operator==(const AscendingIterator& o) const {
        return cont==o.cont && index==o.index;
    }
    bool operator!=(const AscendingIterator& o) const { return !(*this==o); }
    T operator*() const { return cont->data.at(order.at(index)); }
};

template<typename T>
auto MyContainer<T>::begin_ascending_order() const -> AscendingIterator {
    return AscendingIterator(this, 0);
}
template<typename T>
auto MyContainer<T>::end_ascending_order() const -> AscendingIterator {
    return AscendingIterator(this, data.size());
}

// — DescendingIterator —
// Iterates elements in decreasing order.
template<typename T>
class MyContainer<T>::DescendingIterator {
    const MyContainer* cont;
    std::vector<std::size_t> order;
    std::size_t index;

    void initOrder() {
        order.resize(cont->data.size());
        std::iota(order.begin(), order.end(), 0);
        std::sort(order.begin(), order.end(),
                  [&](auto a, auto b){ return cont->data[a] > cont->data[b]; });
    }

public:
    DescendingIterator(const MyContainer* c, std::size_t i)
        : cont(c), index(i) { initOrder(); }

    DescendingIterator& operator++() { ++index; return *this; }
    bool operator==(const DescendingIterator& o) const {
        return cont==o.cont && index==o.index;
    }
    bool operator!=(const DescendingIterator& o) const { return !(*this==o); }
    T operator*() const { return cont->data.at(order.at(index)); }
};

template<typename T>
auto MyContainer<T>::begin_descending_order() const -> DescendingIterator {
    return DescendingIterator(this, 0);
}
template<typename T>
auto MyContainer<T>::end_descending_order() const -> DescendingIterator {
    return DescendingIterator(this, data.size());
}

// — SideCrossIterator —
// Alternates smallest, largest, next-smallest, next-largest...
template<typename T>
class MyContainer<T>::SideCrossIterator {
    const MyContainer* cont;
    std::vector<std::size_t> order;
    std::size_t index;

    void initOrder() {
        const auto n = cont->data.size();
        if (n <= 1) {          // empty or single element
            if (n == 1) order = {0};
            return;
        }
        std::vector<std::size_t> sorted(n);
        std::iota(sorted.begin(), sorted.end(), 0);
        std::sort(sorted.begin(), sorted.end(),
                  [&](auto a, auto b){ return cont->data[a] < cont->data[b]; });
        std::size_t l = 0, r = n-1;
        while (l <= r) {
            order.push_back(sorted[l]);
            if (l < r) order.push_back(sorted[r]);
            ++l; --r;
        }
    }

public:
    SideCrossIterator(const MyContainer* c, std::size_t i)
        : cont(c), index(i) {
        order.reserve(cont->data.size());
        initOrder();
    }

    SideCrossIterator& operator++() { ++index; return *this; }
    bool operator==(const SideCrossIterator& o) const {
        return cont==o.cont && index==o.index;
    }
    bool operator!=(const SideCrossIterator& o) const { return !(*this==o); }
    T operator*() const { return cont->data.at(order.at(index)); }
};

template<typename T>
auto MyContainer<T>::begin_side_cross_order() const -> SideCrossIterator {
    return SideCrossIterator(this, 0);
}
template<typename T>
auto MyContainer<T>::end_side_cross_order() const -> SideCrossIterator {
    return SideCrossIterator(this, data.size());
}

// — ReverseIterator —
// Iterates in reverse insertion order.
template<typename T>
class MyContainer<T>::ReverseIterator {
    const MyContainer* cont;
    std::size_t index;

public:
    ReverseIterator(const MyContainer* c, std::size_t i)
        : cont(c), index(i) {}

    ReverseIterator& operator++() { ++index; return *this; }
    bool operator==(const ReverseIterator& o) const {
        return cont==o.cont && index==o.index;
    }
    bool operator!=(const ReverseIterator& o) const { return !(*this==o); }
    T operator*() const {
        return cont->data.at(cont->data.size()-1-index);
    }
};

template<typename T>
auto MyContainer<T>::begin_reverse_order() const -> ReverseIterator {
    return ReverseIterator(this, 0);
}
template<typename T>
auto MyContainer<T>::end_reverse_order() const -> ReverseIterator {
    return ReverseIterator(this, data.size());
}

// — OrderIterator —
// Standard insertion-order traversal.
template<typename T>
class MyContainer<T>::OrderIterator {
    const MyContainer* cont;
    std::size_t index;

public:
    OrderIterator(const MyContainer* c, std::size_t i)
        : cont(c), index(i) {}

    OrderIterator& operator++() { ++index; return *this; }
    bool operator==(const OrderIterator& o) const {
        return cont==o.cont && index==o.index;
    }
    bool operator!=(const OrderIterator& o) const { return !(*this==o); }
    T operator*() const { return cont->data.at(index); }
};

template<typename T>
auto MyContainer<T>::begin_order() const -> OrderIterator {
    return OrderIterator(this, 0);
}
template<typename T>
auto MyContainer<T>::end_order() const -> OrderIterator {
    return OrderIterator(this, data.size());
}

// — MiddleOutIterator —
// Starts at the middle element, then alternates left and right.
template<typename T>
class MyContainer<T>::MiddleOutIterator {
    const MyContainer* cont;
    std::vector<std::size_t> order;
    std::size_t index;

    void initOrder() {
        const auto n = cont->data.size();
        if (n <= 1) {
            if (n == 1) order = {0};
            return;
        }
        int mid = int(n / 2);
        order.reserve(n);
        order.push_back(mid);
        int l = mid-1, r = mid+1;
        while (order.size() < n) {
            if (l >= 0) order.push_back(size_t(l));
            if (order.size() == n) break;
            if (r < int(n)) order.push_back(size_t(r));
            --l; ++r;
        }
    }

public:
    MiddleOutIterator(const MyContainer* c, std::size_t i)
        : cont(c), index(i) {
        initOrder();
    }

    MiddleOutIterator& operator++() { ++index; return *this; }
    bool operator==(const MiddleOutIterator& o) const {
        return cont==o.cont && index==o.index;
    }
    bool operator!=(const MiddleOutIterator& o) const { return !(*this==o); }
    T operator*() const { return cont->data.at(order.at(index)); }
};

template<typename T>
auto MyContainer<T>::begin_middle_out_order() const -> MiddleOutIterator {
    return MiddleOutIterator(this, 0);
}
template<typename T>
auto MyContainer<T>::end_middle_out_order() const -> MiddleOutIterator {
    return MiddleOutIterator(this, data.size());
}

} // namespace ariel
