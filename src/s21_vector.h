#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <vector>

namespace s21 {
template <typename T>
class Vector {
 public:
  /* TYPES */
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  /*FUNCTIONS*/
  Vector() : size_(0), capacity_(0), arr_(nullptr) {}  // default constructor v
  Vector(size_type n) : size_(n), capacity_(n), arr_(nullptr) {
    arr_ = new value_type[size_];
    for (size_type i = 0; i < size_; i++) {
      arr_[i] = value_type();
    }
  }  // constructor v

  Vector(std::initializer_list<value_type> const &items)
      : Vector(items.size()) {
    std::copy(items.begin(), items.end(), arr_);
  }  // initializer list constructor v

  Vector(const Vector &v) noexcept {
    this->Copy_Vector(v);
  }  // copy construct v

  Vector(Vector &&v) noexcept
      : size_(v.size_), capacity_(v.capacity_), arr_(v.arr_) {
    v.size_ = 0;
    v.capacity_ = 0;
    v.arr_ = nullptr;
  }  // move constructor v
  ~Vector() {
    if (arr_) {
      delete[] arr_;
    }
    size_ = 0;
    capacity_ = 0;
    arr_ = nullptr;
  }  // destructor x

  Vector &Copy_Vector(Vector &v) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    arr_ = new value_type[size_];
    for (size_type i = 0; i < size_; i++) {
      arr_[i] = value_type();
    }
    std::copy(v.arr_, v.arr_ + v.size_, arr_);

    return *this;
  }

  Vector &Copy_Vector(const Vector &v) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    arr_ = new value_type[size_];
    for (size_type i = 0; i < size_; i++) {
      arr_[i] = value_type();
    }
    std::copy(v.arr_, v.arr_ + v.size_, arr_);

    return *this;
  }
  Vector &operator=(Vector &&v) {
    if (arr_ && arr_ != v.arr_) {
      this->~Vector();
    }

    if (arr_ != v.arr_) {
      this->Copy_Vector(v);
    }

    return *this;

  }  // assignment operator v (moves Vector)
  Vector &operator=(const Vector &v) {
    if (arr_ && arr_ != v.arr_) {
      this->~Vector();
    }

    if (arr_ != v.arr_) {
      this->Copy_Vector(v);
    }

    return *this;

  }  // const assignment operator v (copies Vector)

  /*ELEMENT ACCESS*/
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range.");
    }
    return arr_[pos];
  }  // access specified element with bounds checking v
  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range.");
    }
    return arr_[pos];

  }  // access specified const element with bounds checking v
  reference operator[](size_type pos) {
    return at(pos);

  }  // access specified element v

  const_reference operator[](size_type pos) const {
    return at(pos);
  }  // access specified const element v
  const_reference front() { return arr_[0]; }  // access the first element v
  const_reference back() {
    return arr_[size_ - 1];
  }  // access the last element v
  iterator data() noexcept {
    return arr_;
  }  // direct access to the underlying array v

  /*ITERATORS*/
  iterator begin() noexcept {
    return iterator(arr_);
  }  // returns an iterator to the beginning x
  iterator end() noexcept {
    return iterator(arr_ + size_);
  }  // returns an iterator to the end x
  const_iterator cbegin() const noexcept {
    return const_iterator(arr_);
  }  // returns a const iterator to the beginning x
  const_iterator cend() const noexcept {
    return const_iterator(arr_ + size_);
  }  // returns a const iterator to the end x

  /*CAPACITY*/
  bool empty() {
    return size_ == 0;
  }  // checks whether the container is empty x
  size_type size() const { return size_; }  // returns the number of elements x
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(size_type) / 2;
  }  // returns the maximum possible number of elements x
  void reserve(size_type size) {
    if (size > this->max_size()) {
      throw std::length_error("size is bigger than max size of a container");
    } else if (size > capacity_) {
      value_type *temp = new value_type[size]();
      for (size_type i = 0; i < size_; i++) {
        temp[i] = arr_[i];
      }
      delete[] arr_;
      arr_ = temp;
      capacity_ = size;
    }

  }  // allocate storage of size elements and copies current array elements to a
  // newely allocated array x
  size_type capacity() const {
    return capacity_;
  }  // returns the number of elements that can be held in currently allocated
  // storage x
  void shrink_to_fit() {
    capacity_ = size_;
    this->reserve(capacity_);

  }  // reduces memory usage by freeing unused memory x

  /*MODIFIERS*/
  void clear() noexcept { size_ = 0; }  // 	clears the contents x
  iterator insert(iterator pos, const_reference value) {
    if (pos > end() || pos < begin()) {
      throw std::length_error("the pos is unreachable");
    }
    auto new_index = std::distance(begin(), pos);

    if (size_ >= capacity_ - 1) {
      this->reserve((size_ == 0) ? 1 : capacity_ * 2);
    }
    for (long int i = size_; i > new_index; i--) {
      arr_[i] = arr_[i - 1];
    }
    arr_[new_index] = value;
    size_++;
    return begin() + new_index;

  }  // inserts elements into concrete pos and returns the iterator that points
  // to the new element x
  void erase(iterator pos) {
    if (pos > end() || pos < begin()) {
      throw std::length_error("the pos is unreachable");
    }
    auto new_index = pos - begin();
    for (size_type i = new_index; i < size_ - 1; i++) {
      arr_[i] = arr_[i + 1];
    }
    size_--;
  }  // erases element at pos x
  void push_back(const_reference value) {
    Vector<value_type> new_arr(size_ + 1);
    new_arr[size_] = value;
    for (size_type i = 0; i < size_; ++i) {
      new_arr.arr_[i] = arr_[i];
    }
    size_++;
    *this = std::move(new_arr);
  }  // adds an element to the end x
  void pop_back() {
    if (size_ != 0) {
      size_--;
    }

  }  // removes the last element x
  void swap(Vector &other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }  // 	swaps the contents x

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    size_type shift = pos - arr_;  // calculates the shift required to insert
                                   // the element at the given position
    size_type shift_save = shift;  // for later use
    size_type new_size = size_ + sizeof...(args);
    size_type element_place =
        shift + sizeof...(args);  // end position in the vector where new
                                  // elements will be inserted
    auto new_arr =
        arr_;  // assigns the old array pointer to new_array initially

    if (new_size > capacity_) {
      capacity_ = new_size;
      new_arr = new value_type[capacity_];
      for (size_type i = 0; i < shift; i++) {
        new_arr[i] = std::move(arr_[i]);
      }
    }
    size_ = new_size;
    for (auto i = new_size - 1; i >= element_place; i--) {
      new_arr[i] = std::move(arr_[shift + i - element_place]);
    }
    for (auto &&item : {std::forward<Args>(args)...}) {
      new_arr[shift++] = std::move(item);
    }

    if (arr_ != new_arr) {
      delete[] arr_;
      arr_ = new_arr;
    }

    return arr_ + shift_save;
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    emplace(end(), args...);
  }

 private:
  size_type size_;
  size_type capacity_;
  iterator arr_;  // pointer to the first element of Vector
};

template <typename T>
class VectorConstIterator
    : public std::iterator<std::random_access_iterator_tag, T> {
  using value_type = T;
  using const_reference = const T &;
  using const_iterator = const T *;
  friend class Vector<T>;

 public:
  VectorConstIterator() : pointer_(nullptr) {}  // default конструктор итератора

  VectorConstIterator(const_iterator pointer)
      : pointer_(pointer) {}  // конструктор итератора

  bool operator==(VectorConstIterator const &other) const {
    return pointer_ == other.pointer_;
  }
  bool operator!=(VectorConstIterator const &other) const {
    return pointer_ != other.pointer_;
  }
  typename VectorConstIterator::const_reference operator*() const {
    return *pointer_;
  }  // оператор разыменования ссылки для итератора, возвращает ссылку элемента,
  // на который указывает итератор
  VectorConstIterator &operator++() {
    ++pointer_;
    return *this;
  }
  VectorConstIterator &operator--() {
    --pointer_;
    return *this;
  }

 private:
  const_iterator pointer_;
};

template <typename T>
class VectorIterator
    : public std::iterator<std::random_access_iterator_tag, T> {
  using value_type = T;
  using reference = T &;
  using iterator = T *;
  friend class Vector<T>;

 public:
  VectorIterator() : pointer_(nullptr) {}  // default конструктор итератора

  VectorIterator(iterator pointer)
      : pointer_(pointer) {}  // конструктор итератора
  bool operator==(VectorIterator const &other) const {
    return pointer_ == other.pointer_;
  }
  bool operator!=(VectorIterator const &other) const {
    return pointer_ != other.pointer_;
  }
  typename VectorIterator::reference operator*() const {
    return *pointer_;
  }  // оператор разыменования ссылки для итератора, возвращает ссылку элемента,
  // на который указывает итератор
  VectorIterator &operator++() {
    ++pointer_;
    return *this;
  }
  VectorIterator &operator--() {
    --pointer_;
    return *this;
  }

 private:
  iterator pointer_;
};
}  // namespace s21

#endif  // SRC_S21_VECTOR_H_
