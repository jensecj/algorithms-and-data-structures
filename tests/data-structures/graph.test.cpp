#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>

#include <gtest/gtest.h>

#include <data-structures/graph.hpp>

using dads::graphs::adjacency_list;
using dads::graphs::adjacency_matrix;
using dads::graphs::graph;

namespace {

class Graph_AdjacencyList : public ::testing::Test {
 protected:
  std::unique_ptr<graph<adjacency_list>> G;
  void SetUp() override { G = std::make_unique<graph<adjacency_list>>(); }
};

TEST_F(Graph_AdjacencyList, CanAddEdge) {  // NOLINT
  G->add_edge(0, 1, 5);

  int u = G->neighbours(0)[0];

  ASSERT_EQ(u, 1);
  ASSERT_EQ(G->weight(0, u), 5);
}

TEST_F(Graph_AdjacencyList, CanAddBiEdge) {  // NOLINT
  G->add_bi_edge(0, 1, 5);

  int u = G->neighbours(0)[0];
  ASSERT_EQ(u, 1);
  ASSERT_EQ(G->weight(0, u), 5);

  int v = G->neighbours(1)[0];
  ASSERT_EQ(v, 0);
  ASSERT_EQ(G->weight(1, v), 5);
}

TEST_F(Graph_AdjacencyList, CanGetNodes) {  // NOLINT
  G->add_bi_edge(0, 1, 10);
  G->add_bi_edge(1, 2, 10);
  G->add_bi_edge(0, 2, 10);

  std::vector<int> v = G->nodes();
  std::sort(std::begin(v), std::end(v));

  ASSERT_EQ(v[0], 0);
  ASSERT_EQ(v[1], 1);
  ASSERT_EQ(v[2], 2);
}

typedef adjacency_matrix<10> adj_matrix;
class Graph_AdjacencyMatrix : public ::testing::Test {
 protected:
  std::unique_ptr<graph<adj_matrix>> G;
  void SetUp() override { G = std::make_unique<graph<adj_matrix>>(); }
};

TEST_F(Graph_AdjacencyMatrix, CanAddEdge) {  // NOLINT
  G->add_edge(0, 1, 5);

  int u = G->neighbours(0)[0];

  ASSERT_EQ(u, 1);
  ASSERT_EQ(G->weight(0, u), 5);
}

TEST_F(Graph_AdjacencyMatrix, CanAddBiEdge) {  // NOLINT
  G->add_bi_edge(0, 1, 5);

  int u = G->neighbours(0)[0];
  ASSERT_EQ(u, 1);
  ASSERT_EQ(G->weight(0, u), 5);

  int v = G->neighbours(1)[0];
  ASSERT_EQ(v, 0);
  ASSERT_EQ(G->weight(1, v), 5);
}

TEST_F(Graph_AdjacencyMatrix, CanGetNodes) {  // NOLINT
  G->add_bi_edge(0, 1, 10);
  G->add_bi_edge(1, 2, 10);
  G->add_bi_edge(0, 2, 10);

  std::vector<int> v = G->nodes();
  std::sort(std::begin(v), std::end(v));

  ASSERT_EQ(v[0], 0);
  ASSERT_EQ(v[1], 1);
  ASSERT_EQ(v[2], 2);
}

}  // namespace
