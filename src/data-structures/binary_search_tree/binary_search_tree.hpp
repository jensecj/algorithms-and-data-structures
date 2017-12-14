#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP
/*
  The Binary Search Tree.
  Time Complexity: (worst case / average case)
  - space:  O(n)
  - find:   O(n) / O(log n)
  - insert: O(n) / O(log n)
  - remove: O(n) / O(log n)
  - min:    O(log n)
  - max:    O(log n)
  - height: O(log n)
*/

#include <functional>
#include <memory>
#include <optional>
#include <tuple>

namespace dads {

// we can force weak ordering on template-parameters with concepts/constraints
// in c++20
template <class K, class V>
class binary_search_tree {
 private:
  struct node {
    K key;
    V value;
    node *left;
    node *right;

    node(K k, V d) : key(k), value(d), left(nullptr), right(nullptr) {}

    node(const node &) = delete;
    node &operator=(const node &) = default;
    node(node &&) = default;
    node &operator=(node &&) = default;

    ~node() {
      if (left != nullptr) {
        delete left;
        left = nullptr;
      }
      if (right != nullptr) {
        delete right;
        right = nullptr;
      }
    }
  };

  node *_root{nullptr};
  int _nodes{0};
  // private constructor, use empty() to make a new binary_search_tree
  binary_search_tree() = default;

  node *find_recursive(node *n, K key);
  node *find_iterative(node *n, K key);

  void inorder(node *n, std::function<void(std::tuple<K, V>)> callback);
  void preorder(node *n, std::function<void(std::tuple<K, V>)> callback);
  void postorder(node *n, std::function<void(std::tuple<K, V>)> callback);

 public:
  static std::unique_ptr<binary_search_tree<K, V>> empty() {
    return std::unique_ptr<binary_search_tree<K, V>>(
        new binary_search_tree<K, V>);
  }
  static std::unique_ptr<binary_search_tree<K, V>> from(
      std::initializer_list<std::tuple<K, V>> elements) {
    auto bst =
        std::unique_ptr<binary_search_tree<K, V>>(new binary_search_tree<K, V>);

    for (auto kvp : elements) {
      bst->insert(std::get<0>(kvp), std::get<1>(kvp));
    }

    return bst;
  }

  binary_search_tree(const binary_search_tree &) = delete;
  binary_search_tree &operator=(const binary_search_tree &) = delete;
  binary_search_tree(binary_search_tree &&) = delete;
  binary_search_tree &operator=(binary_search_tree &&) = delete;

  ~binary_search_tree() {
    delete _root;
    _root = nullptr;
  }

  bool insert(K key, V value);
  bool remove(K key);
  std::optional<V> find(K key);
  std::optional<std::tuple<K, V>> min();
  std::optional<std::tuple<K, V>> max();
  int height();
  int size();

  void inorder(std::function<void(std::tuple<K, V>)> callback);
  void preorder(std::function<void(std::tuple<K, V>)> callback);
  void postorder(std::function<void(std::tuple<K, V>)> callback);
};

// returns true is data was inserted,
// false if it was already in the tree
template <class K, class V>
bool binary_search_tree<K, V>::insert(K key, V value) {
  // if the root is empty we're inserting into a new tree
  if (_root == nullptr) {
    _nodes++;
    _root = new node(key, value);
    return true;
  }

  // traverse down the tree and find where we need to insert,
  node *cur = _root;
  while (cur != nullptr) {
    // if we're smaller that the current nodes key, move down the left branch
    if (key < cur->key) {
      if (cur->left == nullptr) {
        _nodes++;
        cur->left = new node(key, value);
        return true;
      }
      cur = cur->left;
    }  // if we're bigger than the current nodes key, move down the right
       // branch
    else if (key > cur->key) {
      if (cur->right == nullptr) {
        _nodes++;
        cur->right = new node(key, value);
        return true;
      }
      cur = cur->right;
    } else {
      // do not insert duplicates
      return false;
    }
  }

  return false;
}

// returns true if the key was removed,
// false if key was not found in the tree
template <class K, class V>
bool binary_search_tree<K, V>::remove(K key) {
  node *cur = _root;
  node *parent = nullptr;

  // find the node we're supposed to remove, and remember its parent
  while (cur != nullptr) {
    if (cur->key == key) {
      break;
    }
    parent = cur;
    if (key <= cur->key) {
      cur = cur->left;
    } else if (key > cur->key) {
      cur = cur->right;
    }
  }

  // if we could not find the node, there is nothing to remove
  if (cur == nullptr) {
    return false;
  }

  // the key we're trying to remove is in the root node
  if (parent == nullptr) {
    delete _root;
    _root = nullptr;
    return true;
  }

  // from here on there are three possible cases
  // 1) we're removing a leaf node
  // 2) we're removing a node with a single child
  // 3) we're removing a node with two children

  // removing a leaf node
  if (cur->left == nullptr and cur->right == nullptr) {
    // turn this reference into nullptr
    delete cur;
    cur = nullptr;
    _nodes--;
    return true;
  }

  // removing a node with one child
  bool only_left_child = (cur->left != nullptr or cur->right == nullptr);
  bool only_right_child = (cur->left == nullptr and cur->right != nullptr);
  // connect the only child we have to our parent, essentially taking
  // our place in the tree
  if (only_left_child or only_right_child) {
    if (only_left_child) {
      if (parent->left == cur) {
        parent->left = cur->left;
      } else {
        parent->right = cur->left;
      }
    } else {
      if (parent->left == cur) {
        parent->left = cur->right;
      } else {
        parent->right = cur->right;
      }
    }

    delete cur;
    cur = nullptr;
    _nodes--;
    return true;
  }

  // removing a node with two children
  // we replace outselves with the smallest value in the right subtree
  if (cur->left != nullptr and cur->right != nullptr) {
    node *right_child = cur->right;
    // if our right child is a leaf node, overwrite ourselves with it
    if (right_child->left == nullptr and right_child->right == nullptr) {
      cur->key = right_child->key;
      cur->right = nullptr;
      delete right_child;
      right_child = nullptr;
      _nodes--;
      return true;
    }

    // if our right child has a left child
    // locate the smallest node in its subtree (i.e. the leftmost node)
    if (right_child->left != nullptr) {
      node *right_child_left = right_child->left;
      node *right_child_left_parent = right_child;
      while (right_child_left->left != nullptr) {
        right_child_left_parent = right_child_left;
        right_child_left = right_child_left->left;
      }
      cur->key = right_child_left->key;
      right_child_left_parent->left = nullptr;
      delete right_child_left;
      right_child_left = nullptr;
      _nodes--;
      return true;
    }
    // otherwise we know that our right child is the smallest
    // element in the subtree, everything to the right of it is bigger
    cur->key = right_child->key;
    cur->right = right_child->right;
    delete right_child;
    right_child = nullptr;
    _nodes--;
    return true;
  }

  return false;
}

template <class K, class V>
typename binary_search_tree<K, V>::node *
binary_search_tree<K, V>::find_recursive(node *n, K key) {
  if (n == nullptr) {
    return nullptr;
  }
  if (n->key == key) {
    return n;
  }

  if (key < n->key) {
    return find_recursive(n->left, key);
  }

  return find_recursive(n->right, key);
}

template <class K, class V>
typename binary_search_tree<K, V>::node *
binary_search_tree<K, V>::find_iterative(node *n, K key) {
  node *cur = n;
  while (cur != nullptr) {
    if (cur->key == key) {
      return cur;
    }
    if (key < cur->key) {
      cur = cur->left;
    } else if (key > cur->key) {
      cur = cur->right;
    }
  }

  return cur;
}

// traverse down the tree, looking for some key
template <class K, class V>
std::optional<V> binary_search_tree<K, V>::find(K key) {
  // node *n = find_recursive(_root, key);
  node *n = find_iterative(_root, key);
  return n != nullptr ? std::optional<int>{n->value} : std::nullopt;
}

// returns the (key,value) pair of the smallest value from the tree
template <class K, class V>
std::optional<std::tuple<K, V>> binary_search_tree<K, V>::min() {
  if (_root == nullptr) return std::nullopt;

  node *cur = _root;
  while (cur->left != nullptr) {
    cur = cur->left;
  }
  return std::make_tuple(cur->key, cur->value);
}

// returns the (key,value) pair of the biggest value from the tree
template <class K, class V>
std::optional<std::tuple<K, V>> binary_search_tree<K, V>::max() {
  if (_root == nullptr) return std::nullopt;

  node *cur = _root;
  while (cur->right != nullptr) {
    cur = cur->right;
  }
  return std::make_tuple(cur->key, cur->value);
}

// how many levels the tree has
template <class K, class V>
int binary_search_tree<K, V>::height() {
  if (_root == nullptr) {
    return -1;
  }

  node *cur_left = _root;
  node *cur_right = _root;

  // why is this the case? why can we only have cases where the tree
  // is bigger in either the smallest or biggest positions? (i.e. all
  // left, or all right)
  int left_height = 0, right_height = 0;
  while (cur_left != nullptr) {
    left_height++;
    cur_left = cur_left->left;
  }
  while (cur_right != nullptr) {
    right_height++;
    cur_right = cur_right->right;
  }

  return std::max(left_height, right_height);
}

// the number of nodes in the tree
template <class K, class V>
int binary_search_tree<K, V>::size() {
  return _nodes;
}

template <class K, class V>
void binary_search_tree<K, V>::inorder(
    node *n, std::function<void(std::tuple<K, V>)> callback) {
  if (n->left != nullptr) {
    inorder(n->left, callback);
  }

  callback({n->key, n->value});

  if (n->right != nullptr) {
    inorder(n->right, callback);
  }
}

template <class K, class V>
void binary_search_tree<K, V>::inorder(
    std::function<void(std::tuple<K, V>)> callback) {
  inorder(_root, callback);
}

template <class K, class V>
void binary_search_tree<K, V>::preorder(
    node *n, std::function<void(std::tuple<K, V>)> callback) {
  callback({n->key, n->value});

  if (n->left != nullptr) {
    preorder(n->left, callback);
  }

  if (n->right != nullptr) {
    preorder(n->right, callback);
  }
}

template <class K, class V>
void binary_search_tree<K, V>::preorder(
    std::function<void(std::tuple<K, V>)> callback) {
  preorder(_root, callback);
}

template <class K, class V>
void binary_search_tree<K, V>::postorder(
    node *n, std::function<void(std::tuple<K, V>)> callback) {
  if (n->left != nullptr) {
    postorder(n->left, callback);
  }

  if (n->right != nullptr) {
    postorder(n->right, callback);
  }

  callback({n->key, n->value});
}

template <class K, class V>
void binary_search_tree<K, V>::postorder(
    std::function<void(std::tuple<K, V>)> callback) {
  postorder(_root, callback);
}

}  // namespace dads

#endif
