#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>

#include <gtest/gtest.h>

#include <algorithms/breadth_first_search.hpp>
#include <algorithms/depth_first_search.hpp>
#include <data-structures/graph.hpp>

using dads::graphs::adjacency_list;
using dads::graphs::graph;

namespace {

class DFSSearchableGraph : public ::testing::Test {
 protected:
  std::unique_ptr<graph<adjacency_list>> G;
  void SetUp() override { G = std::make_unique<graph<adjacency_list>>(); }
};

TEST_F(DFSSearchableGraph, DFSCanFindShortestReach) {  // NOLINT
  G->add_bi_edge(1, 2, 1);
  G->add_bi_edge(2, 3, 1);
  G->add_bi_edge(3, 4, 1);
  G->add_bi_edge(4, 5, 1);
  G->add_bi_edge(5, 1, 1);
  G->add_bi_edge(5, 6, 1);
  G->add_bi_edge(6, 7, 1);
  G->add_bi_edge(7, 8, 1);
  G->add_bi_edge(7, 1, 1);
  G->add_bi_edge(1, 9, 1);
  G->add_bi_edge(1, 11, 1);
  G->add_bi_edge(11, 10, 1);
  G->add_bi_edge(11, 12, 1);
  G->add_bi_edge(12, 13, 1);

  auto r = dads::graphs::dfs_shortest_reach<graph<adjacency_list>>(*G, 1);

  for (auto[k, v] : r) {
    std::cout << k << "," << v << "\n";
  }

  // int u = G->neighbours(0)[0];

  // ASSERT_EQ(u, 1);
  // ASSERT_EQ(G->weight(0, u), 5);
}

}  // namespace
