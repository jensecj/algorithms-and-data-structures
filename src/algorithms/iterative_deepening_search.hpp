#ifndef ITERATIVE_DEEPENING_SEARCH_HPP
#define ITERATIVE_DEEPENING_SEARCH_HPP
/*
  Depth first search, and related algorithms.
*/

#include <functional>
#include <limits>
#include <memory>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <algorithms/depth_first_search.hpp>
#include <data-structures/graph.hpp>

namespace dads::graphs {

template <typename T>
static bool iterative_deepening_bfs(
    T& graph, int source, int goal, int max_depth,
    std::function<void(int parent, int node)> visit) {
  bool found = false;
  int depth;
  for (depth = 0; depth <= max_depth; depth++) {
    dads::graphs::depth_first_search(
        graph, source,
        [&graph, &goal, &visit, &found](int parent, int node) {
          visit(parent, node);
          if (node == goal) {
            found = true;
          }
        },
        depth);

    if (found) {
      break;
    }
  }

  return found;
}

}  // namespace dads::graphs

#endif
