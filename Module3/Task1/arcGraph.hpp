// Copyright 2021 Ilyagu Nagdimaev

#ifndef MODULE3_TASK1_ARCGRAPH_HPP_
#define MODULE3_TASK1_ARCGRAPH_HPP_

#include <utility>
#include <vector>

#include "iGraph.hpp"

class ArcGraph : public IGraph {
 public:
  explicit ArcGraph(size_t verticesCount);

  explicit ArcGraph(const IGraph& imageGraph);

  void AddEdge(int from, int to) override;

  [[nodiscard]] size_t VerticesCount() const override;

  [[nodiscard]] std::vector<int> GetChildren(int vertex) const override;

  [[nodiscard]] std::vector<int> GetParents(int vertex) const override;

 private:
  std::vector<std::pair<int, int>> _graph;
};

#endif  // MODULE3_TASK1_ARCGRAPH_HPP_
