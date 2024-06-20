#ifndef S21_LIST_H
#define S21_LIST_H

#include <iostream>
#include <limits>
#include <utility>

namespace s21 {
template <typename T>
struct Node {
  Node *next;
  Node *prev;
  T value;

  Node() : next(nullptr), prev(nullptr), value() {}
  Node(const T val) : next(nullptr), prev(nullptr), value(val) {}
};

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator;

template <typename T>
class list {
 public:
  // List Member type

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;

 private:
  size_type size_;
  Node<T> *base_;

  void init() { base_->next = base_->prev = base_; }

  void add_node(Node<T> *value, Node<T> *after_value) {
    value->prev = after_value->prev;
    value->next = after_value;
    after_value->prev->next = value;
    after_value->prev = value;
    ++size_;
    //            base_->value = size_;
  }

  void remove_node(Node<T> *node_to_delete) {
    Node<T> *next = node_to_delete->next, *prev = node_to_delete->prev;
    next->prev = prev;
    prev->next = next;
    delete node_to_delete;
    --size_;
    //            base_->value = size_;
  }

 public:
  // List Functions

  list() : size_(0), base_(new Node<T>()) { init(); }

  list(size_type n) : list() {
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const &items) : list() {
    for (auto const &item : items) {
      push_back(item);
    }
  }

  list(const list &other) : list() {
    Node<T> *current = other.base_->next;
    while (current != other.base_) {
      push_back(current->value);
      current = current->next;
    }
  }

  list(list &&other) : size_(other.size_), base_(other.base_) {
    other.size_ = 0;
    other.base_ = nullptr;
  }

  // Move assignment operator
  list &operator=(list &&l) noexcept {
    if (this != &l) {
      clear();
      delete base_;
      size_ = l.size_;
      base_ = l.base_;
      l.base_ = nullptr;
      l.size_ = 0;
    }
    return *this;
  }

  // Copy assignment operator
  list &operator=(const list &l) {
    if (this != &l) {
      clear();
      for (Node<T> *current = l.base_->next; current != l.base_;
           current = current->next) {
        push_back(current->value);
      }
    }
    return *this;
  }

  ~list() {
    clear();
    delete base_;
  }

  // List Element access - done

  const_reference front() { return base_->next->value; }

  const_reference back() { return base_->prev->value; }

  // List Iterators

  iterator begin() { return iterator(base_->next); }
  iterator end() { return iterator(base_); }

  const_iterator cbegin() const { return const_iterator(base_->next); }
  const_iterator cend() const { return const_iterator(base_); }

  // List Capacity - done

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 12;
  }

  // List Modifiers

  void clear() {
    while (size_ > 0) {
      pop_front();
    }
  }

  iterator insert(iterator pos, const_reference value) {
    Node<T> *node = new Node<T>(value);
    if (!node) throw std::bad_alloc();
    add_node(node, pos.node_);
    return iterator(node);
  }

  iterator erase(iterator pos) {
    if (pos.node_ != base_) {
      iterator next = pos.node_->next;
      remove_node(pos.node_);
      return next;
    } else {
      throw std::out_of_range("Can't erase from end of list");
    }
  }

  void push_front(const_reference value) {
    Node<T> *node = new Node<T>(value);
    if (!node) throw std::bad_alloc();
    add_node(node, base_->next);
  }

  void push_back(const_reference value) {
    Node<T> *node = new Node<T>(value);
    if (!node) throw std::bad_alloc();
    add_node(node, base_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    return insert(pos, value_type(std::forward<Args>(args)...));
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    push_back(value_type(std::forward<Args>(args)...));
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    push_front(value_type(std::forward<Args>(args)...));
  }

  void pop_front() {
    if (size_ <= 0) {
      throw std::out_of_range("Can't pop from empty list");
    }
    remove_node(base_->next);
  }

  void pop_back() {
    if (size_ <= 0) {
      throw std::out_of_range("Can't pop from empty list");
    }
    remove_node(base_->prev);
  }

  void swap(list &other) noexcept {
    std::swap(size_, other.size_);
    std::swap(base_, other.base_);
  }

  void resize(size_type count) {
    int counter = count - size_;
    if (counter > 0) {
      for (int i = 0; i < counter; ++i) push_back(value_type());
    } else {
      counter *= -1;
      for (int i = 0; i < counter; ++i) pop_back();
    }
  }

  // List Operations

  void merge(list &other) {
    if (this != &other) {
      for (list<T>::iterator it = this->begin();
           it != this->end() && !other.empty();) {
        if (*it >= other.front()) {
          this->insert(it, other.front());
          other.pop_front();
        } else {
          it++;
        }
      }
      while (!other.empty()) {
        this->push_back(other.front());
        other.pop_front();
      }
    }
  }

  void splice(const_iterator pos, list &other) {
    if (this != &other) {
      size_type size = other.size();
      for (size_type i = 0; i < size; ++i) {
        insert(pos, other.front());
        other.pop_front();
      }
    }
  }

  void reverse() {
    Node<T> *current = base_;
    do {
      std::swap(current->prev, current->next);
      current = current->next;
    } while (current != base_);
  }

  void unique() {
    for (Node<T> *node = base_->next; node != base_->prev; node = node->next) {
      if (node->next->value == node->value) {
        remove_node(node->next);
        node = node->prev;
      }
    }
  }

  void sort() {
    for (Node<T> *current = base_->next; current != base_;
         current = current->next) {
      for (Node<T> *next = current->next; next != base_; next = next->next) {
        if (current->value > next->value) {
          std::swap(current->value, next->value);
        }
      }
    }
  }

  // List Helpers

  void print() {
    if (!this->empty()) {
      for (Node<T> *node = base_->next; node != base_; node = node->next) {
        std::cout << node->value << " ";
      }
      std::cout << std::endl;
    }
  }
};

template <typename T>
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
 public:
  using reference = T &;
  using pointer = T *;

  ListIterator() : node_(nullptr) {}
  ListIterator(Node<T> *node) : node_(node) {}

  ListIterator &operator++() {
    node_ = node_->next;
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  ListIterator &operator--() {
    node_ = node_->prev;
    return *this;
  }

  ListIterator operator--(int) {
    ListIterator tmp(*this);
    --(*this);
    return tmp;
  }

  bool operator==(const ListIterator<T> &other) const {
    return node_ == other.node_;
  }

  bool operator!=(const ListIterator<T> &other) const {
    return node_ != other.node_;
  }

  reference operator*() { return node_->value; }
  pointer operator->() const { return &node_->value; }

 protected:
  Node<T> *node_;

  friend class list<T>;
};

template <typename T>
class ListConstIterator : public ListIterator<T> {
 public:
  using const_reference = const T &;

  ListConstIterator() : ListIterator<T>() {}
  // создание константного итератора из обычного
  ListConstIterator(const ListIterator<T> &it) : ListIterator<T>(it) {}
  // создание копии константного итератора current
  ListConstIterator(const ListConstIterator &it) : ListIterator<T>(it) {}

  const_reference operator*() const { return this->node_->value; }
};
}  // namespace s21

#endif  // S21_LIST_H
