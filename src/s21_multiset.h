#ifndef SRC_S21_MULTISET_H
#define SRC_S21_MULTISET_H

#include "s21_tree.h"

namespace s21 {
template <typename Key>
class multiset {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using tree = RBTree<value_type>;
  using size_type = std::size_t;

 public:
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;

  multiset() : tree_(){};

  multiset(std::initializer_list<value_type> const& items) {
    for (auto it : items) {
      tree_.insert_duplicate(it);
    }
  };

  multiset(const multiset& s) : tree_(s.tree_){};

  multiset(multiset&& s) : tree_(std::move(s.tree_)){};

  ~multiset() = default;

  multiset& operator=(const multiset& other) {
    tree_ = other.tree_;
    return *this;
  };

  multiset& operator=(multiset&& other) {
    tree_ = std::move(other.tree_);
    return *this;
  }

  iterator insert(const_reference key) { return tree_.insert_duplicate(key); };

  void erase(iterator pos) { tree_.erase(pos); };

  bool empty() const noexcept { return tree_.empty(); };

  size_type size() const noexcept { return tree_.size(); };

  size_type max_size() const noexcept { return tree_.max_size(); };

  void clear() { tree_.clear(); };

  void swap(multiset& other) { tree_.swap(other.tree_); };

  void merge(multiset& other) { tree_.merge_duplicates(other.tree_); };

  iterator find(const_reference key) noexcept { return tree_.find(key); };

  const_iterator find(const_reference key) const noexcept {
    return tree_.find(key);
  };

  bool contains(const_reference key) const noexcept {
    return tree_.contains(key);
  };

  iterator begin() noexcept { return tree_.begin(); };

  const_iterator begin() const noexcept { return tree_.begin(); };

  iterator end() noexcept { return tree_.end(); };

  const_iterator end() const noexcept { return tree_.end(); };

  size_type count(const_reference key) const noexcept {
    return tree_.count(key);
  };

  std::pair<iterator, iterator> equal_range(const_reference key) noexcept {
    return tree_.equal_range(key);
  };

  iterator lower_bound(const_reference key) noexcept {
    return tree_.lower_bound(key);
  };

  iterator upper_bound(const_reference key) noexcept {
    return tree_.upper_bound(key);
  };

  std::pair<const_iterator, const_iterator> equal_range(
      const_reference key) const noexcept {
    return tree_.equal_range(key);
  };

  const_iterator lower_bound(const_reference key) const noexcept {
    return tree_.lower_bound(key);
  };

  const_iterator upper_bound(const_reference key) const noexcept {
    return tree_.upper_bound(key);
  };

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return tree_.insert_many_duplicate(std::forward<Args>(args)...);
  };

 private:
  tree tree_;
};
}  // namespace s21

#endif  // SRC_S21_MULTISET_H