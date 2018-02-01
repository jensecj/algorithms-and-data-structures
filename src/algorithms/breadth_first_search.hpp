#ifndef BREADTH_FIRST_SEARCH_HPP
#define BREADTH_FIRST_SEARCH_HPP
/*
  Breadth first search, and related algorithms.
*/

#include <functional>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

#include <data-structures/graph.hpp>

namespace dads::graphs {

template <typename T>
static void breadth_first_search(
    T& graph, int source, std::function<void(int parent, int node)> visit) {
  std::unordered_map<int, bool> seen;

  std::queue<int> queue;
  queue.push(source);

  seen[source] = true;

  while (!queue.empty()) {
    const int c = queue.front();
    queue.pop();

    for (const int n : graph.neighbours(c)) {
      // if we have not visited this node yet, the distance is not set
      if (!seen[n]) {
        visit(c, n);
        seen[n] = true;
        queue.push(n);
      }
    }
  }
}

// finds the shortest reach from some node to all other nodes in the
// graph
template <typename T>
static std::unordered_map<int, int> bfs_shortest_reach(T& graph, int source) {
  std::unordered_map<int, int> distances;

  breadth_first_search(
      graph, source, [&distances, &graph](int parent, int node) {
        distances[node] = distances[parent] + graph.weight(parent, node);
      });

  return distances;
}

}  // namespace dads::graphs

#endif
