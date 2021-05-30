// Copyright 2021 Ilyagu Nagdimaev

#ifndef MODULE3_TASK1_SETGRAPH_HPP_
#define MODULE3_TASK1_SETGRAPH_HPP_

#include <set>
#include <vector>

#include "iGraph.hpp"

class SetGraph : public IGraph {
 public:
  explicit SetGraph(size_t verticesCount);

  explicit SetGraph(const IGraph& imageGraph);

  void AddEdge(int from, int to) override;

  [[nodiscard]] size_t VerticesCount() const override;

  [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

  [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  std::vector<std::set<int>> _graph;
};

#endif  // MODULE3_TASK1_SETGRAPH_HPP_
