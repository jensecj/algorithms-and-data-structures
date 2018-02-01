#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>

#include <gtest/gtest.h>

#include <algorithms/breadth_first_search.hpp>
#include <data-structures/graph.hpp>

using dads::graphs::adjacency_list;
using dads::graphs::graph;

namespace {

class BFSSearchableGraph : public ::testing::Test {
 protected:
  std::unique_ptr<graph<adjacency_list>> G;
  void SetUp() override { G = std::make_unique<graph<adjacency_list>>(); }
};

TEST_F(BFSSearchableGraph, CanFindShortestReach) {  // NOLINT
  G->add_bi_edge(0, 1, 5);
  G->add_edge(1, 4, 2);

  auto r = dads::graphs::bfs_shortest_reach<graph<adjacency_list>>(*G, 1);

  for (auto[k, v] : r) {
    std::cout << k << "," << v << "\n";
  }

  // int u = G->neighbours(0)[0];

  // ASSERT_EQ(u, 1);
  // ASSERT_EQ(G->weight(0, u), 5);
}

}  // namespace
