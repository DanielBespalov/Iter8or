# Iter8or
A header-only C++ template container with six custom iterator orders:

- **Ascending** (smallest → largest)  
- **Descending** (largest → smallest)  
- **Side-Cross** (smallest, largest, 2nd smallest, 2nd largest, …)  
- **Reverse** (reverse insertion)  
- **Insertion** (order elements were added)  
- **Middle-Out** (middle, left of middle, right of middle, …)

Supports `addElement()`, `removeElement()`, `size()`, and streaming via `operator<<`. Fully tested with [`doctest`](https://github.com/onqtam/doctest).

---

## Table of Contents

- [Features](#features)  
- [File Structure](#file-structure)  
- [Building & Running](#building--running)  

---

## Features

- **Template-based**: works with any `T` that is `<`- and `==`-comparable (including built-ins, `std::string`, custom structs).  
- **Six iterator types** with `begin_…()/end_…()` pairs.  
- **Exception safety**: `removeElement()` throws `std::runtime_error` if element not found.  
- **Header-only** interface in `MyContainer.hpp`.  
- **Lightweight**: no raw pointers, uses `std::vector` internally.  

---

## File Structure
├── Demo.cpp # simple main() demonstrating MyContainer usage

├── MyContainer.hpp # public interface & inline template definitions

├── MyContainer_impl.cpp # template implementation (included by .hpp)

├── test.cpp # full doctest suite, including BENCHMARK for performance

├── doctest.h # header-only testing framework

└── Makefile # build, run, test, valgrind


## Building & Running
# Build and run Demo.cpp, then run all tests:
make

# Just build & run the demo:
make Main

# Valgrind Memory Check:
make valgrind

# Just build & run the test suite:
make test



