#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <vector>

namespace s21 {
template <typename T, size_t N>
class Array {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  /*Member functions*/
  Array() : size_(N) {}
  Array(std::initializer_list<value_type> const &items) : Array() {
    if (items.size() > size_) {
      throw std ::out_of_range("List is bigger than array");
    }
    size_type i = 0;
    for (auto elem : items) {
      arr_[i++] = elem;
    }
  }
  Array(const Array &a) noexcept : Array() {
    for (size_t i = 0; i < size_; i++) {
      arr_[i] = a.arr_[i];
    }
  }
  Array(Array &&a) noexcept : Array() {
    if (this != &a) {
      std::move(a.cbegin(), a.cend(), arr_);
    }
  }

  ~Array(){};

  Array operator=(Array &&a) {
    this->fill(0);
    if (this != &a) {
      std::move(a.cbegin(), a.cend(), arr_);
    }

    return *this;
  }

  Array operator=(Array &a) {
    this->fill(0);
    for (size_t i = 0; i < size_; i++) {
      arr_[i] = a.arr_[i];
    }

    return *this;
  }

  /*Element Access*/

  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range.");
    }
    return arr_[pos];
  }  // access specified element with bounds checking
  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range.");
    }
    return arr_[pos];
  }

  reference operator[](size_type pos) {
    return at(pos);
  }  // access specified element
  const_reference operator[](size_type pos) const { return at(pos); }

  const_reference front() const { return arr_[0]; }  // access the first element
  const_reference back() const {
    return arr_[size_ - 1];
  }  // access the last element
  iterator data() noexcept {
    return arr_;
  }  // direct access to the underlying array

  /*Array Iterators*/
  iterator begin() noexcept {
    return arr_;
  }  // returns an iterator to the beginning
  iterator end() noexcept {
    return &arr_[size_];
  }  // returns an iterator to the end
  const_iterator cbegin() const noexcept {
    return arr_;
  }  // returns an iterator to the beginning
  const_iterator cend() const noexcept {
    return &arr_[size_];
  }  // returns an iterator to the end

  /*Array Capacity*/
  bool empty() { return size_ == 0; }  // checks whether the container is empty
  size_type size() { return size_; }   // returns the number of elements
  size_type max_size() {
    return size_;
  }  // returns the maximum possible number of elements

  /*Array Modifiers*/
  void swap(Array &other) noexcept {
    std::swap(this->arr_, other.arr_);
  }  // swaps the contents
  void fill(const_reference value) {
    for (size_type i = 0; i < size_; i++) {
      arr_[i] = value;
    }
  }  // assigns the given value value to all elements in the container.

 private:
  size_type size_;
  value_type arr_[N];
};
}  // namespace s21

#endif  // SRC_S21_ARRAY_H_