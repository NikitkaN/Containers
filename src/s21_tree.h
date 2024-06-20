#ifndef SRC_S21_TREE_H_
#define SRC_S21_TREE_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace s21 {
template <typename Key>
class RBTree {
  class RBTreeNode;
  class RBTreeIterator;
  class RBTreeConstIterator;
  using reference = Key&;
  using const_reference = const Key&;
  using Node_P = RBTreeNode*;
  using size_type = std::size_t;
  using comparator = std::less<Key>;

  enum NodeColor { BL, RD };

 public:
  using value_type = Key;
  using iterator = RBTreeIterator;
  using const_iterator = RBTreeConstIterator;

  RBTree() : root_(new RBTreeNode), size_(0){};

  RBTree(const RBTree& other) : RBTree() { *this = other; };

  RBTree(RBTree&& other) : RBTree() { *this = std::move(other); };

  ~RBTree() {
    clear();
    delete_node(root_);
  };

  RBTree& operator=(const RBTree& other) {
    if (this != &other) {
      if (other.size_ == 0) {
        clear();
      } else {
        if (root_->parent_) clear();
        Node_P root = copy(other.root_->parent_, nullptr);
        root_->parent_ = root;
        root_->parent_->parent_ = root;
        root_->left_ = other.root_->left_;
        root_->right_ = other.root_->right_;
        size_ = other.size_;
      }
    }
    return *this;
  };

  RBTree& operator=(RBTree&& other) {
    if (this != &other) {
      clear();
      std::swap(this->root_, other.root_);
      std::swap(this->size_, other.size_);
    } else {
      other.clear();
      delete_node(other.root_);
    }
    return *this;
  };

  iterator begin() noexcept {
    if (size_ == 0) return iterator(root_);
    return iterator(root_->left_);
  };

  const_iterator begin() const noexcept {
    return const_iterator(root_->left_);
  };

  iterator end() noexcept { return iterator(root_); };

  const_iterator end() const noexcept { return const_iterator(root_); };

  bool empty() const noexcept { return size_ ? 0 : 1; };

  size_type size() const noexcept { return size_; };

  size_type max_size() const noexcept {
    long int size = (std::numeric_limits<size_type>::max() / 2 -
                     sizeof(RBTreeNode) - sizeof(RBTree)) /
                    sizeof(RBTreeNode);
    if (size_ == 0) return size;
    return size;
  };

  void clear() {
    delete_all(root_->parent_);
    root_->parent_ = nullptr;
    root_->left_ = nullptr;
    root_->right_ = nullptr;
    size_ = 0;
  };

  std::pair<iterator, bool> insert(const value_type& value) {
    Node_P new_node = new RBTreeNode(value);
    std::pair<iterator, bool> res = insert_node(new_node, true);
    if (!res.second) delete_node(new_node);
    return res;
  };

  iterator insert_duplicate(const value_type& value) {
    Node_P new_node = new RBTreeNode(value);
    return insert_node(new_node, false).first;
  };

  void erase(iterator pos) { delete_node(pos); };

  void swap(RBTree& other) {
    using std::swap;
    swap(root_, other.root_);
    swap(size_, other.size_);
  };

  iterator find(const_reference key) noexcept {
    iterator res = iterator(find_node(key));
    if (res == end() || comparator{}(*res, key)) return end();
    return res;
  };

  const_iterator find(const_reference key) const noexcept {
    const_iterator res = lower_bound(key);
    if (res == end() || comparator{}(*res, key)) return end();
    return res;
  };

  bool contains(const_reference key) const noexcept {
    Node_P node = find_node(key);
    return (node != root_);
  };

  iterator upper_bound(const_reference value) noexcept {
    iterator result = end();
    Node_P begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(value, begin->data_)) {
        result = iterator(begin);
        begin = begin->left_;
      } else
        begin = begin->right_;
    }
    return result;
  };

  const_iterator upper_bound(const_reference value) const noexcept {
    const_iterator result = end();
    Node_P begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(value, begin->data_)) {
        result = const_iterator(begin);
        begin = begin->left_;
      } else
        begin = begin->right_;
    }
    return result;
  };

  iterator lower_bound(const_reference value) noexcept {
    iterator result = end();
    Node_P begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(begin->data_, value)) {
        begin = begin->right_;
      } else {
        result = iterator(begin);
        begin = begin->left_;
      }
    }
    return result;
  };

  const_iterator lower_bound(const_reference value) const noexcept {
    const_iterator result = end();
    Node_P begin = root_->parent_;
    while (begin != nullptr) {
      if (comparator{}(begin->data_, value)) {
        begin = begin->right_;
      } else {
        result = const_iterator(begin);
        begin = begin->left_;
      }
    }
    return result;
  };

  size_type count(const_reference key) const noexcept {
    const_iterator it = begin();
    size_type c = 0;
    for (size_type i = 0; i < size(); i++) {
      if (*it == key) c++;
      it++;
    }
    return c;
  };

  std::pair<iterator, iterator> equal_range(const_reference key) noexcept {
    iterator start = lower_bound(key), end = upper_bound(key);
    return {start, end};
  };

  std::pair<const_iterator, const_iterator> equal_range(
      const_reference key) const noexcept {
    const_iterator start = lower_bound(key), end = upper_bound(key);
    return {start, end};
  };

  void merge_duplicates(RBTree& other) noexcept {
    if (this != &other) {
      iterator it = other.begin();
      while (other.size_ > 0) {
        Node_P node = it.node_;
        it++;
        if (node->parent_->left_ == node) node->parent_->left_ = nullptr;
        if (node->parent_->right_ == node) node->parent_->right_ = nullptr;
        if (node->right_) node->right_->parent_ = node->parent_;
        if (node->left_) node->left_->parent_ = node->parent_;
        node->left_ = nullptr;
        node->right_ = nullptr;
        node->parent_ = nullptr;
        node->color_ = RD;
        insert_node(node, false);
        other.size_--;
      }
    }
    other.root_->parent_ = nullptr;
    other.size_ = 0;
  };

  void merge(RBTree& other) noexcept {
    if (this != &other) {
      iterator it = other.begin();
      while (it != other.end()) {
        if (find(it.node_->data_) == end()) {
          Node_P node = it.node_;
          it++;
          node = other.merge_Node(node);
          insert_node(node, true);
        } else
          it++;
      }
    }
  };

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vect;
    vect.reserve(sizeof...(args));
    for (auto element : {std::forward<Args>(args)...}) {
      Node_P new_node = new RBTreeNode(std::move(element));
      std::pair<iterator, bool> result = insert_node(new_node, true);
      if (result.second == false) {
        delete new_node;
      }
      vect.push_back(result);
    }
    return vect;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many_duplicate(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vect;
    vect.reserve(sizeof...(args));
    for (auto element : {std::forward<Args>(args)...}) {
      Node_P new_node = new RBTreeNode(std::move(element));
      vect.push_back(insert_node(new_node, false));
    }
    return vect;
  }

 private:
  std::pair<iterator, bool> insert_node(Node_P new_node, bool unique) {
    Node_P node = root_->parent_;
    Node_P parent = nullptr;
    while (node != nullptr) {
      parent = node;
      if (comparator{}(new_node->data_, node->data_))
        node = node->left_;
      else if (comparator{}(node->data_, new_node->data_))
        node = node->right_;
      else if (unique == false)
        node = node->right_;
      else
        return {iterator(node), false};
    }
    size_++;
    if (parent == nullptr) {
      new_node->parent_ = root_;
      root_->parent_ = new_node;
      new_node->color_ = BL;
    } else {
      new_node->parent_ = parent;
      comparator{}(new_node->data_, parent->data_) ? parent->left_ = new_node
                                                   : parent->right_ = new_node;
    }
    if (!root_->right_ || root_->right_->right_) {
      root_->right_ = new_node;
    }
    if (!root_->left_ || root_->left_->left_) root_->left_ = new_node;
    balance_insert(new_node);
    return {iterator(new_node), true};
  };

  void delete_node(Node_P node) {
    if (node != nullptr) {
      node->left_ = nullptr;
      node->right_ = nullptr;
      node->parent_ = nullptr;
      delete node;
      node = nullptr;
    }
  };

  void left_rotate(Node_P node) noexcept {
    Node_P help_node = node->right_;
    node->right_ = help_node->left_;
    if (help_node->left_ != nullptr) {
      help_node->left_->parent_ = node;
    }
    help_node->parent_ = node->parent_;
    if (node->parent_ == root_) {
      root_->parent_ = help_node;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = help_node;
    } else {
      node->parent_->right_ = help_node;
    }
    help_node->left_ = node;
    node->parent_ = help_node;
  };

  void right_rotate(Node_P node) noexcept {
    Node_P help_node = node->left_;
    node->left_ = help_node->right_;
    if (help_node->right_ != nullptr) {
      help_node->right_->parent_ = node;
    }
    help_node->parent_ = node->parent_;
    if (root_->parent_ == node) {
      root_->parent_ = help_node;
    } else if (node == node->parent_->right_) {
      node->parent_->right_ = help_node;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = help_node;
    }
    help_node->right_ = node;
    node->parent_ = help_node;
  };

  void balance_insert(Node_P node) noexcept {
    Node_P u;
    while (node->parent_->color_ == RD && node != root_->parent_) {
      if (node->parent_ == node->parent_->parent_->right_) {
        u = node->parent_->parent_->left_;
        if (u != nullptr && u->color_ == RD) {
          u->color_ = BL;
          node->parent_->color_ = BL;
          node->parent_->parent_->color_ = RD;
          node = node->parent_->parent_;
        } else {
          if (node == node->parent_->left_) {
            node = node->parent_;
            right_rotate(node);
          }
          node->parent_->color_ = BL;
          node->parent_->parent_->color_ = RD;
          left_rotate(node->parent_->parent_);
        }
      } else {
        u = node->parent_->parent_->right_;
        if (u != nullptr && u->color_ == RD) {
          u->color_ = BL;
          node->parent_->color_ = BL;
          node->parent_->parent_->color_ = RD;
          node = node->parent_->parent_;
        } else {
          if (node == node->parent_->right_) {
            node = node->parent_;
            left_rotate(node);
          }
          node->parent_->color_ = BL;
          node->parent_->parent_->color_ = RD;
          right_rotate(node->parent_->parent_);
        }
      }
    }
    root_->parent_->color_ = BL;
  };

  Node_P search_right(Node_P node) noexcept {
    while (node->right_) {
      node = node->right_;
    }
    return node;
  };

  Node_P search_Left(Node_P node) noexcept {
    while (node->left_) {
      node = node->left_;
    }
    return node;
  };

  void swap_Nodes(Node_P one, Node_P two) noexcept {
    two == two->parent_->left_ ? two->parent_->left_ = one
                               : two->parent_->right_ = one;
    if (one == root_->parent_)
      root_->parent_ = two;
    else
      one == one->parent_->left_ ? one->parent_->left_ = two
                                 : one->parent_->right_ = two;
    std::swap(one->left_, two->left_);
    std::swap(one->right_, two->right_);
    std::swap(one->parent_, two->parent_);
    std::swap(one->color_, two->color_);
    if (one->left_) one->left_->parent_ = one;
    if (one->right_) one->right_->parent_ = one;
    if (two->left_) two->left_->parent_ = two;
    if (two->right_) two->right_->parent_ = two;
  };

  Node_P find_node(const_reference key) const noexcept {
    Node_P ptr = root_->parent_;
    while (ptr) {
      if (ptr->data_ == key) return ptr;
      if (comparator{}(ptr->data_, key))
        ptr = ptr->right_;
      else
        ptr = ptr->left_;
    }
    return root_;
  };

  Node_P find_node(iterator pos) const noexcept {
    Node_P res = find_node(*pos);
    return res;
  };

  void delete_node(iterator pos) {
    if (pos == end()) return;
    Node_P node = pos.node_;
    if (node->left_ && node->right_) {
      Node_P swap_node = search_right(node->left_);
      swap_Nodes(node, swap_node);
    }
    if (!node->left_ && node->right_ != nullptr) {
      swap_Nodes(node, node->right_);
    }
    if (!node->right_ && node->left_ != nullptr) {
      swap_Nodes(node, node->left_);
    }
    if (node->color_ == BL && (!node->left_ && !node->right_)) {
      balance_delete(node);
    }
    if (root_->parent_ == node) {
      root_->parent_ = nullptr;
      root_->right_ = nullptr;
      root_->left_ = nullptr;
    } else {
      node->parent_->left_ == node ? node->parent_->left_ = nullptr
                                   : node->parent_->right_ = nullptr;
      if (root_->left_ == node) root_->left_ = search_Left(root_->parent_);
      if (root_->right_ == node) root_->right_ = search_right(root_->parent_);
    }
    delete_node(node);
    size_--;
  };

  Node_P merge_Node(Node_P node) {
    if (node != root_) {
      if (node->right_ && node->left_) {
        Node_P swap = search_right(node->left_);
        swap_Nodes(node, swap);
      }
      if (node->right_ && !node->left_) swap_Nodes(node, node->right_);
      if (node->left_ && !node->right_) swap_Nodes(node, node->left_);
      if (node->color_ == BL && (!node->right_ && !node->left_))
        balance_delete(node);
      if (root_->left_ == node) root_->left_ = node->successor();
      if (root_->right_ == node) root_->right_ = node->predecessor();
      if (root_->parent_ == node)
        root_->parent_ = nullptr;
      else
        node->parent_->left_ == node ? node->parent_->left_ = nullptr
                                     : node->parent_->right_ = nullptr;
      size_--;
      node->left_ = nullptr;
      node->right_ = nullptr;
      node->parent_ = nullptr;
      node->color_ = RD;
      return node;
    }
    return nullptr;
  }

  void balance_delete(Node_P node) {
    Node_P s = nullptr;
    while (node != root_->parent_ && node->color_ == BL) {
      if (node == node->parent_->left_) {
        s = node->parent_->right_;
        if (s->color_ == RD) {
          std::swap(s->color_, node->parent_->color_);
          left_rotate(node->parent_);
          s = node->parent_->right_;
        }
        if (s->color_ == BL && (!s->left_ || s->left_->color_ == BL) &&
            (!s->right_ || s->right_->color_ == BL)) {
          s->color_ = RD;
          if (node->parent_->color_ == RD) {
            node->parent_->color_ = BL;
            break;
          }
          node = node->parent_;
        } else {
          if (!s->right_ || s->right_->color_ == BL) {
            s->color_ = RD;
            s->left_->color_ = BL;
            right_rotate(s);
            s = node->parent_->right_;
          }
          s->color_ = node->parent_->color_;
          s->right_->color_ = BL;
          node->parent_->color_ = BL;
          left_rotate(node->parent_);
          break;
        }
      } else {
        s = node->parent_->left_;
        if (s->color_ == RD) {
          std::swap(s->color_, node->parent_->color_);
          right_rotate(node->parent_);
          s = node->parent_->left_;
        }
        if (s->color_ == BL && (!s->left_ || s->left_->color_ == BL) &&
            (!s->right_ || s->right_->color_ == BL)) {
          s->color_ = RD;
          if (node->parent_->color_ == RD) {
            node->parent_->color_ = BL;
            break;
          }
          node = node->parent_;
        } else {
          if (!s->left_ || s->left_->color_ == BL) {
            s->color_ = RD;
            s->right_->color_ = BL;
            left_rotate(s);
            s = node->parent_->left_;
          }
          s->color_ = node->parent_->color_;
          s->left_->color_ = BL;
          node->parent_->color_ = BL;
          right_rotate(node->parent_);
          break;
        }
      }
    }
    root_->parent_->color_ = BL;
  };

  void delete_all(Node_P node) {
    if (node == nullptr) return;
    delete_all(node->left_);
    delete_all(node->right_);
    delete_node(node);
  };

  Node_P copy(Node_P copy_node, Node_P parent) {
    Node_P new_node = new RBTreeNode(copy_node);
    if (copy_node->left_) new_node->left_ = copy(copy_node->left_, new_node);
    if (copy_node->right_) new_node->right_ = copy(copy_node->right_, new_node);
    new_node->parent_ = parent;
    return new_node;
  };

  class RBTreeNode {
   public:
    RBTreeNode()
        : data_(Key{}),
          color_(RD),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr){};

    RBTreeNode(const Key& value)
        : data_(value),
          color_(RD),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr){};

    RBTreeNode(const Key&& value)
        : data_(std::move(value)),
          color_(RD),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr){};

    RBTreeNode(RBTreeNode* node)
        : data_(node->data_),
          color_(node->color_),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr){};

    Key data_;
    NodeColor color_;
    Node_P parent_;
    Node_P left_;
    Node_P right_;

    Node_P successor() noexcept {
      Node_P node = this;
      if (node->color_ == RD &&
          (node->parent_ == nullptr || node->parent_->parent_ == node)) {
        return node->right_;
      } else if (node->right_ != nullptr) {
        node = node->right_;
        while (node->left_ != nullptr) node = node->left_;
      } else {
        Node_P parent = node->parent_;
        while (node == parent->right_) {
          node = parent;
          parent = parent->parent_;
        }
        if (node->right_ != parent) node = parent;
      }
      return node;
    };

    Node_P predecessor() noexcept {
      Node_P node = this;
      if (node->color_ == RD &&
          (node->parent_ == nullptr || node->parent_->parent_ == node))
        return node->right_;
      else if (node->left_ != nullptr) {
        node = node->left_;
        while (node->right_ != nullptr) node = node->right_;
      } else {
        Node_P parent = node->parent_;
        while (node == parent->left_) {
          node = parent;
          parent = parent->parent_;
        }
        if (node->left_ != parent) node = parent;
      }
      return node;
    };
  };

  class RBTreeIterator {
    friend RBTree;

   public:
    RBTreeIterator() : node_(nullptr){};
    RBTreeIterator(Node_P node) : node_(node){};
    reference operator*() noexcept { return node_->data_; };

    bool operator==(const iterator& other) noexcept {
      return node_ == other.node_;
    };

    bool operator!=(const iterator& other) noexcept {
      return node_ != other.node_;
    };

    iterator& operator++() noexcept {
      node_ = node_->successor();
      return *this;
    };

    iterator operator++(int) noexcept {
      iterator temp(node_);
      ++(*this);
      return temp;
    };

    iterator& operator--() noexcept {
      node_ = node_->predecessor();
      return *this;
    };

    iterator operator--(int) noexcept {
      iterator temp(node_);
      --(*this);
      return temp;
    };

   private:
    Node_P node_;
  };

  class RBTreeConstIterator {
    friend RBTree;

   public:
    RBTreeConstIterator() : node_(nullptr){};
    RBTreeConstIterator(const iterator& other) { node_ = other.node_; };
    const_reference operator*() const noexcept { return node_->data_; };

    const_iterator operator++() noexcept {
      node_ = node_->successor();
      return *this;
    };

    const_iterator operator++(int) noexcept {
      const_iterator temp(*this);
      ++(*this);
      return temp;
    };

    const_iterator operator--() noexcept {
      node_ = node_->predecessor();
      return *this;
    }

    const_iterator operator--(int) noexcept {
      const_iterator temp(*this);
      --(*this);
      return temp;
    };

   private:
    Node_P node_;
    friend bool operator==(const const_iterator& it1,
                           const const_iterator& it2) noexcept {
      return it1.node_ == it2.node_;
    };

    friend bool operator!=(const const_iterator& it1,
                           const const_iterator& it2) noexcept {
      return it1.node_ != it2.node_;
    };
  };

  Node_P root_ = nullptr;
  size_type size_{};
};
}  // namespace s21

#endif  // SRC_S21_TREE_H_