#ifndef SRC_S21_STACK_H__
#define SRC_S21_STACK_H__

#include "s21_list.h"

namespace s21 {
template <typename T>
class stack : private s21::list<T> {
 public:
  using list = s21::list<T>;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = s21::ListIterator<T>;
  using size_type = size_t;

  // Stack Operations

  using list::list;  // Constructors

  // Stack Element access

  const_reference top() { return list::back(); }

  // Stack Capacity

  using list::empty;
  using list::size;

  // Stack Modifiers

  void push(const_reference value) { list::push_back(value); }

  void pop() { list::pop_back(); }

  template <typename... Args>
  void emplace(Args &&...args) {
    list::emplace_back(std::forward<Args>(args)...);
  }

  void swap(stack &other) { list::swap(static_cast<list &>(other)); }

  using list::print;
};
}  // namespace s21

#endif  // SRC_S21_STACK_H__
