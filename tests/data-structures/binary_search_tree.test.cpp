#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>

#include <gtest/gtest.h>

#include <data-structures/binary_search_tree.hpp>

using dads::trees::binary_search_tree;

namespace {

/////////////
// GENERAL //
/////////////
class BinarySearchTree : public ::testing::Test {
 protected:
  std::unique_ptr<binary_search_tree<int, int>> bst;
  void SetUp() override {
    bst = std::make_unique<binary_search_tree<int, int>>();
  }
};

TEST_F(BinarySearchTree, EmptyTreeHasZeroSizeAndHeight) {  // NOLINT
  ASSERT_EQ(bst->size(), 0);
  ASSERT_EQ(bst->height(), 0);
}

TEST_F(BinarySearchTree, DoNotAllowDuplicates) {  // NOLINT
  ASSERT_TRUE(bst->insert(1, 13));
  ASSERT_FALSE(bst->insert(1, 13));
}

TEST_F(BinarySearchTree, CannotRemoveFromEmpty) {  // NOLINT
  ASSERT_EQ(bst->size(), 0);
  ASSERT_FALSE(bst->remove(1));
}

TEST_F(BinarySearchTree, CanGetMin) {  // NOLINT
  bst->insert(1, 10);
  bst->insert(2, 20);
  bst->insert(3, 30);

  auto kvp = bst->min();

  ASSERT_TRUE(kvp);
  ASSERT_EQ(std::get<0>(*kvp), 1);
  ASSERT_EQ(std::get<1>(*kvp), 10);
}

TEST_F(BinarySearchTree, CanGetMax) {  // NOLINT
  bst->insert(1, 10);
  bst->insert(2, 20);
  bst->insert(3, 30);

  auto kvp = bst->max();

  ASSERT_TRUE(kvp);
  ASSERT_EQ(std::get<0>(*kvp), 3);
  ASSERT_EQ(std::get<1>(*kvp), 30);
}

TEST_F(BinarySearchTree, Grows) {  // NOLINT
  for (int i = 0; i < 10000; i++) {
    bst->insert(i, i);
  }
  ASSERT_GT(bst->height(), 5);
}

TEST_F(BinarySearchTree, CanFindNodePresentInTree) {  // NOLINT
  for (int i = 0; i < 1000; i++) {
    bst->insert(i, i);
  }
  ASSERT_TRUE(bst->find(321));
}

class TraversableBinarySearchTree : public ::testing::Test {
 protected:
  std::unique_ptr<binary_search_tree<int, int>> bst;
  void SetUp() override {
    std::initializer_list<std::tuple<int, int>> elements = {
        {3, 3}, {1, 1}, {5, 5}, {0, 0}, {2, 2}, {4, 4}, {6, 6}};
    bst = std::make_unique<binary_search_tree<int, int>>(elements);
  }
};

TEST_F(TraversableBinarySearchTree, CanTraverseInorder) {  // NOLINT
  std::string s;
  bst->inorder(
      [&s](std::tuple<int, int> n) { s += std::to_string(std::get<1>(n)); });

  ASSERT_EQ("0123456", s);
}

TEST_F(TraversableBinarySearchTree, CanTraversePreorder) {  // NOLINT
  std::string s;
  bst->preorder(
      [&s](std::tuple<int, int> n) { s += std::to_string(std::get<1>(n)); });

  ASSERT_EQ("3102546", s);
}

TEST_F(TraversableBinarySearchTree, CanTraversePostorder) {  // NOLINT
  std::string s;
  bst->postorder(
      [&s](std::tuple<int, int> n) { s += std::to_string(std::get<1>(n)); });

  ASSERT_EQ("0214653", s);
}

//////////
// INTS //
//////////
class IntBinarySearchTree : public ::testing::Test {
 protected:
  std::unique_ptr<binary_search_tree<int, int>> bst;
  void SetUp() override {
    bst = std::make_unique<binary_search_tree<int, int>>();
  }
};

TEST_F(IntBinarySearchTree, CanInsert) {  // NOLINT
  ASSERT_TRUE(bst->insert(1, 2));
  ASSERT_EQ(bst->size(), 1);
  ASSERT_EQ(bst->height(), 1);
}

TEST_F(IntBinarySearchTree, CanFind) {  // NOLINT
  ASSERT_TRUE(bst->insert(1, 4242));
  ASSERT_EQ(bst->find(1), 4242);
}

TEST_F(IntBinarySearchTree, CanRemove) {  // NOLINT
  ASSERT_TRUE(bst->insert(1, 4242));
  ASSERT_TRUE(bst->remove(1));
  ASSERT_FALSE(bst->find(1));
}

/////////////
// STRINGS //
/////////////
class StringBinarySearchTree : public ::testing::Test {
 protected:
  std::unique_ptr<binary_search_tree<std::string, int>> bst;
  void SetUp() override {
    bst = std::make_unique<binary_search_tree<std::string, int>>();
  }
};

TEST_F(StringBinarySearchTree, CanInsert) {  // NOLINT
  ASSERT_TRUE(bst->insert("some key", 2));
  ASSERT_EQ(bst->size(), 1);
  ASSERT_EQ(bst->height(), 1);
}

TEST_F(StringBinarySearchTree, CanFind) {  // NOLINT
  ASSERT_TRUE(bst->insert("some key", 4242));
  ASSERT_EQ(bst->find("some key"), 4242);
}

TEST_F(StringBinarySearchTree, CanRemove) {  // NOLINT
  ASSERT_TRUE(bst->insert("some key", 4242));
  ASSERT_TRUE(bst->remove("some key"));
  ASSERT_FALSE(bst->find("some key"));
}

}  // namespace
