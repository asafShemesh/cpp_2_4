//asaf0604@gmail.com   325362457

# MyContainer Project

A generic, template-based container class in C++ supporting multiple iteration orders (e.g., ascending, descending, side-cross, middle-out, etc.), implemented with modern C++ (C++17), with full test coverage using the `doctest` framework.

## 📦 Overview

`MyContainer<T>` is a custom container that:
- Stores elements of any type `T`
- Allows adding/removing elements
- Supports multiple custom iterators:
  - Ascending order
  - Descending order
  - Side-cross order
  - Reverse order
  - Original insertion order
  - Middle-out order

## 🧩 Features

- Fully templated design
- Iterator support with custom traversal patterns
- Exception-safe operations
- Doctest-based test suite for all functions and edge cases

---

## 🛠️ Installation & Compilation

```bash
make        # builds main executable
make test   # builds test suite (requires doctest)
./main      # run the demo
./test      # run all unit tests
```

---

## 📚 Class: `MyContainer<T>`

### `void addElement(const T& val)`
Adds an element to the container.

### `void removeElement(const T& val)`
Removes the first occurrence of the value from the container.  
Throws `std::runtime_error` if the element is not found.

### `size_t size() const`
Returns the number of elements currently stored.

### `const std::vector<T>& get_data() const`
Returns a read-only reference to the internal vector.  
Useful for direct inspection or integration.

---

## 🔁 Iterator Types

All iterators support the following operations:
- `T operator*()` – dereference to get the current element
- `Iterator& operator++()` – advance to the next element
- `bool operator!=(const Iterator& other)` – inequality check

Each iterator has corresponding `begin_*` and `end_*` methods.

---

### 🔼 `AscendingOrder`
Iterates elements in ascending sorted order.

```cpp
for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
    std::cout << *it << ' ';
}
```

---

### 🔽 `DescendingOrder`
Iterates elements in descending sorted order.

---

### 🔀 `SideCrossOrder`
Alternates between the smallest and largest remaining elements, inward:
e.g., for sorted `[1, 2, 3, 4, 5]` → `1, 5, 2, 4, 3`

---

### 🔁 `ReverseOrder`
Iterates elements in reverse of their original insertion order.

---

### 🧾 `Order`
Iterates elements in their original insertion order (FIFO).

---

### 🎯 `MiddleOutOrder`
Starts from the middle of the sorted list and moves outward:
e.g., for sorted `[1, 2, 3, 4, 5]` → `3, 5, 1, 4, 2`

---

## 🧪 Testing

- Tests are located in `test_my_container_doctest.cpp`
- Run with `make test && ./test`
- Uses `doctest` to verify:
  - Correct iteration orders
  - Edge cases like empty containers
  - Exception handling for invalid operations
  - All public methods

---

## 📂 File Structure

```
.
├── main.cpp                 # Demonstration program
├── my_container.hpp         # Main header with class & iterators
├── Makefile                 # Build rules
├── test_my_container_doctest.cpp  # Full unit test suite
└── README.md                # Project documentation
```
