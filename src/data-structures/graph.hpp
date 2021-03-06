#ifndef GRAPH_HPP
#define GRAPH_HPP
/*
  A minimal graph structure.
  Can use either an adjacency list or an adjacency matrix as a
  representation for edges between nodes.
*/

#include <functional>
#include <memory>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace dads::graphs {

class node_store {
 public:
  virtual void add_edge(int u, int v, int w) = 0;
  virtual std::vector<int> nodes() = 0;
  virtual std::vector<int> neighbours(int n) = 0;
  virtual int weight(int u, int v) = 0;
};

class adjacency_list : public node_store {
  /*
    In an adjacency list, each node keeps a list of it's edges to other nodes
    that their costs.
    If the nodes in the graph have a relatively small degree, then this can save
    a lot of space for big graphs.
    But if we have a graph where most nodes have edges to most other nodes, we
    end up with a lot of double-record-keeping.
   */
 private:
  std::unordered_map<int, std::unordered_map<int, int>> list;

 public:
  void add_edge(int u, int v, int weight) override { list[u][v] = weight; }

  std::vector<int> nodes() override {
    std::vector<int> ns;

    // nodes are saved as (node, edges[]) pairs, grab all nodes
    for (auto pair : list) {
      ns.push_back(std::get<0>(pair));
    }

    return ns;
  }

  std::vector<int> neighbours(int n) override {
    std::vector<int> ns;
    // the neighbours of a node are stores a list of (node, weight) pairs, grab
    // all neighbours
    for (auto pair : list[n]) {
      ns.push_back(std::get<0>(pair));
    }

    return ns;
  }

  int weight(int u, int v) override { return list[u][v]; }
};

template <const std::size_t N>
class adjacency_matrix : public node_store {
  /*
    An adjacency matrix stores all nodes and their edges as a 2d-matrix, where
    graph[A][B] indicates the weight of the edge from A to B.
   */
 private:
  std::vector<std::vector<int>> matrix;

 public:
  adjacency_matrix() : matrix(N, std::vector<int>(N, -1)) {}

  void add_edge(int u, int v, int weight) override { matrix[u][v] = weight; }

  std::vector<int> nodes() override {
    std::vector<int> ns;

    for (std::size_t i = 0; i < N; i++) {
      for (std::size_t j = 0; j < N; j++) {
        // TODO: handle negative weight edges
        if (matrix[i][j] > -1) {
          ns.push_back(i);
          break;
        }
      }
    }

    return ns;
  }

  std::vector<int> neighbours(int n) override {
    std::vector<int> ns;

    for (std::size_t i = 0; i < N; i++) {
      // TODO: handle negative weight edges
      if (matrix[n][i] > -1) {
        ns.push_back(i);
      }
    }

    return ns;
  }

  int weight(int u, int v) override { return matrix[u][v]; }
};

template <typename T>
class graph {
 private:
  std::unique_ptr<T> _nodes;

  graph(const graph &) = delete;
  graph &operator=(const graph &) = delete;
  graph(graph &&) = delete;
  graph &operator=(graph &&) = delete;

 public:
  graph() : _nodes(std::move(std::make_unique<T>())){};

  void add_edge(int u, int v, int weight);
  void add_bi_edge(int u, int v, int weight);
  std::vector<int> nodes();
  std::vector<int> neighbours(int n);
  int weight(int u, int v);
};

template <typename T>
void graph<T>::add_edge(int u, int v, int weight) {
  _nodes->add_edge(u, v, weight);
}

template <typename T>
void graph<T>::add_bi_edge(int u, int v, int weight) {
  _nodes->add_edge(u, v, weight);
  _nodes->add_edge(v, u, weight);
}

template <typename T>
std::vector<int> graph<T>::nodes() {
  return _nodes->nodes();
}

template <typename T>
std::vector<int> graph<T>::neighbours(int n) {
  return _nodes->neighbours(n);
}

template <typename T>
int graph<T>::weight(int u, int v) {
  return _nodes->weight(u, v);
}

}  // namespace dads::graphs

#endif
