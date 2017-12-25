#ifndef GRAPH_UTILS_HPP
#define GRAPH_UTILS_HPP
/*
  Utilities for working with graphs
*/
#include <sstream>

#include <data-structures/graph.hpp>

using dads::graphs::graph;

namespace dads::graphs {

template <typename T>
static std::string to_csv(T& graph) {
  std::ostringstream ss;

  auto gs = graph.nodes();
  std::sort(std::begin(gs), std::end(gs));

  for (auto u : gs) {
    auto ns = graph.neighbours(u);
    std::sort(std::begin(ns), std::end(ns));

    for (auto v : ns) {
      ss << u << "," << v << "," << graph.weight(u, v) << " ";
    }
  }

  // don't include the trailing space
  std::string csv = ss.str();
  return csv.substr(0, csv.size() - 1);
}

template <typename T>
static std::unique_ptr<T> from_csv(std::string& csv) {
  auto G = T::make();

  std::istringstream ss(csv);
  std::string token;
  while (std::getline(ss, token, ' ')) {
    std::vector<int> nums(3);

    std::istringstream line(token);

    for (int i = 0; i < 3; i++) {
      std::getline(line, token, ',');
      nums[i] = std::stoi(token);
    }

    G->add_edge(nums[0], nums[1], nums[2]);
  }

  return G;
}

}  // namespace dads::graphs

#endif
