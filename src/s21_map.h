#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include "s21_tree.h"

namespace s21 {
template <typename Key, typename T>
class map {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using tree = RBTree<value_type>;
  using size_type = std::size_t;

 public:
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;

  map() = default;

  map(std::initializer_list<value_type> const& items) {
    for (auto it : items) {
      tree_.insert(it);
    }
  };

  map(const map& m) : tree_(m.tree_){};

  map(map&& m) : tree_(std::move(m.tree_)){};

  ~map() = default;

  map& operator=(map& m) {
    tree_ = m.tree_;
    return *this;
  };

  map& operator=(map&& m) {
    tree_ = std::move(m.tree_);
    return *this;
  };

  T& at(const Key& key) {
    iterator it = map_find(key);
    if (it == tree_.end()) throw std::out_of_range("map::at");
    return (*it).second;
  };

  const T& at(const Key& key) const {
    const_iterator it = map_find(key);
    if (it == tree_.end()) throw std::out_of_range("map::at");
    return (*it).second;
  };

  T& operator[](const Key& key) {
    value_type value = {key, mapped_type{}};
    iterator it = map_find(key);
    if (it == tree_.end()) {
      auto res = tree_.insert(value);
      return (*res.first).second;
    }
    return (*it).second;
  }

  iterator begin() noexcept { return tree_.begin(); };

  iterator end() noexcept { return tree_.end(); };

  const_iterator begin() const noexcept { return tree_.begin(); };

  const_iterator end() const noexcept { return tree_.end(); };

  bool empty() const noexcept { return tree_.empty(); };

  size_type size() const noexcept { return tree_.size(); };

  size_type max_size() const noexcept { return tree_.max_size(); };

  void clear() { tree_.clear(); };

  std::pair<iterator, bool> insert(const value_type& value) {
    iterator it = map_find(value.first);
    if (it == end()) {
      auto res = tree_.insert(value);
      return res;
    }
    return {it, false};
  };

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    value_type value = {key, obj};
    iterator it = map_find(value.first);
    if (it == end()) {
      auto res = tree_.insert(value);
      return res;
    }
    return {it, false};
  };

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    value_type value = {key, obj};
    iterator it = map_find(key);
    if (it == tree_.end())
      return tree_.insert(value);
    else {
      (*it).second = obj;
      return {it, false};
    }
  };

  void erase(iterator pos) {
    auto it = map_find((*pos).first);
    if (it != end()) tree_.erase(pos);
  };

  void swap(map& other) { tree_.swap(other.tree_); };

  void merge(map& other) { tree_.merge(other.tree_); };

  bool contains(const Key& key) const noexcept {
    const_iterator it = map_find(key);
    return it == end() ? 0 : 1;
  };

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return tree_.insert_many(std::forward<Args>(args)...);
  };

 private:
  iterator map_find(const Key& key) noexcept {
    iterator it = tree_.begin();
    if (it == tree_.end() || it == nullptr) return end();
    while (it != tree_.end()) {
      if ((*it).first == key) return it;
      it++;
    }
    return end();
  }

  const_iterator map_find(const Key& key) const noexcept {
    const_iterator it = tree_.begin();
    if (it == tree_.end()) return end();
    while (it != tree_.end()) {
      if ((*it).first == key) return it;
      it++;
    }
    return end();
  }

  tree tree_{};
};
}  // namespace s21

#endif  // SRC_S21_MAP_H_