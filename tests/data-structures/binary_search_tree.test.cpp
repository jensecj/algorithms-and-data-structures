#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>

#include <gtest/gtest.h>

#include "binary_search_tree/binary_search_tree.hpp"

using dads::binary_search_tree;

namespace {

/////////////
// GENERAL //
/////////////
class BinarySearchTree : public ::testing::Test {
 protected:
  std::unique_ptr<binary_search_tree<int, int>> bst;
  void SetUp() override { bst = binary_search_tree<int, int>::empty(); }
  void TearDown() override { bst.reset(); }
};

TEST_F(BinarySearchTree, EmptyTreeHasSizeZero) {  // NOLINT
  ASSERT_EQ(bst->size(), 0);
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

  auto[k, v] = bst->min();
  ASSERT_EQ(k, 1);
  ASSERT_EQ(v, 10);
}

TEST_F(BinarySearchTree, CanGetMax) {  // NOLINT
  bst->insert(1, 10);
  bst->insert(2, 20);
  bst->insert(3, 30);

  auto[k, v] = bst->max();
  ASSERT_EQ(k, 3);
  ASSERT_EQ(v, 30);
}

TEST_F(BinarySearchTree, Grows) {  // NOLINT
  for (int i = 0; i < 10000; i++) {
    bst->insert(i, i);
  }
  ASSERT_GT(bst->height(), 5);
}

TEST_F(BinarySearchTree, CanFindNodePresentInTree) {  // NOLINT
  bst->insert(1, 321);
  for (int i = 0; i < 1000; i++) {
    bst->insert(i, i);
  }
  ASSERT_TRUE(bst->find(321));
}

//////////
// INTS //
//////////
class IntBinarySearchTree : public ::testing::Test {
 protected:
  std::unique_ptr<binary_search_tree<int, int>> bst;
  void SetUp() override { bst = binary_search_tree<int, int>::empty(); }
  void TearDown() override { bst.reset(); }
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
  void SetUp() override { bst = binary_search_tree<std::string, int>::empty(); }
  void TearDown() override { bst.reset(); }
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
