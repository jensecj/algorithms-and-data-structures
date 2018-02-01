#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>

#include <gtest/gtest.h>

#include <algorithms/graph_utils.hpp>
#include <data-structures/graph.hpp>

using dads::graphs::adjacency_list;
using dads::graphs::graph;

namespace {

class SomeGraph : public ::testing::Test {
 protected:
  std::unique_ptr<graph<adjacency_list>> G;
  void SetUp() override { G = std::make_unique<graph<adjacency_list>>(); }
};

TEST_F(SomeGraph, CanConvertFromCsvToGraph) {  // NOLINT
  G->add_edge(0, 1, 1);
  G->add_edge(0, 2, 1);

  G->add_edge(1, 3, 2);
  G->add_edge(1, 4, 2);
  G->add_edge(2, 5, 2);
  G->add_edge(2, 6, 2);

  std::string g = dads::graphs::to_csv(*G);
  std::cout << g << '\n';

  ASSERT_TRUE(true);
}

TEST_F(SomeGraph, CanConvertFromGraphToCsv) {  // NOLINT
  std::string graph_str = "0,1,1 0,2,1 1,3,2 1,4,2 2,5,2 2,6,2";
  auto G = dads::graphs::from_csv<graph<adjacency_list>>(graph_str);

  ASSERT_EQ(G->weight(0, 2), 1);
  ASSERT_EQ(G->weight(0, 1), 1);
  ASSERT_EQ(G->weight(1, 3), 2);
  ASSERT_EQ(G->weight(1, 4), 2);
  ASSERT_EQ(G->weight(2, 5), 2);
  ASSERT_EQ(G->weight(2, 6), 2);
}

TEST_F(SomeGraph, GraphConversionsAreInverses) {  // NOLINT
  std::string graph_str = "0,1,1 0,2,1 1,3,2 1,4,2 2,5,2 2,6,2";
  auto G = dads::graphs::from_csv<graph<adjacency_list>>(graph_str);

  std::string new_graph_str = dads::graphs::to_csv(*G);
  auto new_G = dads::graphs::from_csv<graph<adjacency_list>>(new_graph_str);

  ASSERT_EQ(graph_str, new_graph_str);
  ASSERT_EQ(G->nodes(), new_G->nodes());
}

}  // namespace
