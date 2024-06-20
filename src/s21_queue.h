#ifndef SRC_S21_QUEUE_H__
#define SRC_S21_QUEUE_H__

#include "s21_list.h"

namespace s21 {
template <typename T>
class queue : private s21::list<T> {
 public:
  using list = s21::list<T>;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Queue Operations

  using list::list;  // Constructors

  // Queue Element access

  using list::back;
  using list::front;

  // Queue Capacity

  using list::empty;
  using list::size;

  // Queue Modifiers

  void push(const_reference value) { list::push_back(value); }

  void pop() { list::pop_front(); }

  template <typename... Args>
  void insert_many(Args &&...args) {
    list::insert_many_back(std::forward<Args>(args)...);
  }

  void swap(queue &other) { list::swap(static_cast<list &>(other)); }

  using list::print;
};
}  // namespace s21

#endif  // SRC_S21_QUEUE_H__
