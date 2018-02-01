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
static std::string to_csv(T& graph, const char seperator = ' ') {
  std::ostringstream ss;

  // we store all nodes and their neighbours in sorted order, just to make
  // testing easier.
  auto nodes = graph.nodes();
  std::sort(std::begin(nodes), std::end(nodes));

  for (auto u : nodes) {
    auto neighbours = graph.neighbours(u);
    std::sort(std::begin(neighbours), std::end(neighbours));

    for (auto v : neighbours) {
      ss << u << "," << v << "," << graph.weight(u, v) << seperator;
    }
  }

  // don't include the trailing space
  std::string csv = ss.str();
  return csv.substr(0, csv.size() - 1);
}

template <typename T>
static std::unique_ptr<T> from_csv(std::string& csv,
                                   const char seperator = ' ') {
  auto G = std::make_unique<T>();

  std::istringstream ss(csv);
  std::string token;
  while (std::getline(ss, token, seperator)) {
    // the node record saves is on the form (from, to, weight)
    std::vector<int> record(3);

    std::istringstream line(token);

    for (int i = 0; i < 3; i++) {
      std::getline(line, token, ',');
      record[i] = std::stoi(token);
    }

    G->add_edge(record[0], record[1], record[2]);
  }

  return G;
}

}  // namespace dads::graphs

#endif
