#ifndef DEPTH_FIRST_SEARCH_HPP
#define DEPTH_FIRST_SEARCH_HPP
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

#include <data-structures/graph.hpp>

namespace dads::graphs {

template <typename T>
static void depth_first_search(
    T& graph, int source, std::function<void(int parent, int node)> visit,
    int max_depth = std::numeric_limits<int>::max()) {
  // push first element to stack, and everytime we find a new
  // undiscovered vertex, we push it to the stack as well, typical
  // rewrite of a recursive program to use stacks instead of recursion

  // each element is a (parent, node, depth) tuple
  std::stack<std::tuple<int, int, int>> stack;
  stack.push({source, source, 0});

  std::unordered_map<int, bool> seen;

  // keep looking at nodes as long as we have some in the stack
  while (!stack.empty()) {
    auto[parent, node, depth] = stack.top();
    stack.pop();

    // if a node is not yet seen, examine it
    if (!seen[node] and depth <= max_depth) {
      seen[node] = true;
      visit(parent, node);

      // add all neighbours that are not yet seen to the stack
      for (const int& n : graph.neighbours(node)) {
        stack.push({node, n, depth + 1});
      }
    }
  }
}

// finds the shortest reach from some node to all other nodes in the
// graph, using depth-first-search
template <typename T>
static std::unordered_map<int, int> dfs_shortest_reach(T& graph, int source) {
  std::unordered_map<int, int> distances;

  depth_first_search(graph, source, [&distances, &graph](int parent, int node) {
    const int dist = distances[parent] + graph.weight(parent, node);
    if (!distances[node] or distances[node] > dist) {
      distances[node] = distances[parent] + graph.weight(parent, node);
    }
  });

  return distances;
}

}  // namespace dads::graphs

#endif
