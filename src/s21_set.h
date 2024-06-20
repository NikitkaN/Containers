#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include "s21_tree.h"

namespace s21 {
template <typename Key>
class set {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using tree = RBTree<value_type>;
  using size_type = std::size_t;

 public:
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;

  set() : tree_(){};

  set(std::initializer_list<value_type> const& items) {
    for (auto it : items) {
      tree_.insert(it);
    }
  };

  set(const set& s) : tree_(s.tree_){};

  set(set&& s) : tree_(std::move(s.tree_)){};

  ~set() = default;

  set& operator=(const set& other) {
    tree_ = other.tree_;
    return *this;
  };

  set& operator=(set&& other) {
    tree_ = std::move(other.tree_);
    return *this;
  }

  std::pair<iterator, bool> insert(const_reference key) {
    return tree_.insert(key);
  };

  size_type size() const noexcept { return tree_.size(); };

  size_type max_size() const noexcept { return tree_.max_size(); };

  void erase(iterator pos) { tree_.erase(pos); };

  bool empty() const noexcept { return tree_.empty(); };

  void clear() { tree_.clear(); };

  void swap(set& other) { tree_.swap(other.tree_); };

  void merge(set& other) noexcept { tree_.merge(other.tree_); };

  bool contains(const_reference key) const { return tree_.contains(key); };

  iterator find(const_reference key) { return tree_.find(key); };

  const_iterator find(const_reference key) const { return tree_.find(key); };

  iterator begin() noexcept { return tree_.begin(); };

  const_iterator begin() const noexcept { return tree_.begin(); };

  iterator end() noexcept { return tree_.end(); };

  const_iterator end() const noexcept { return tree_.end(); };

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return tree_.insert_many(std::forward<Args>(args)...);
  };

 private:
  tree tree_;
};
}  // namespace s21

#endif  // SRC_S21_SET_H_