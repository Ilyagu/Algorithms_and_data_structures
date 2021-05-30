// Copyright 2021 Ilyagu Nagdimaev

#ifndef MODULE3_TASK1_LISTGRAPH_HPP_
#define MODULE3_TASK1_LISTGRAPH_HPP_

#include <algorithm>
#include <vector>

#include "iGraph.hpp"

class ListGraph : public IGraph {
 public:
  explicit ListGraph(size_t verticesCount);

  explicit ListGraph(const IGraph& imageGraph);

  ~ListGraph() override = default;

  // Добавление ребра от from к to.
  void AddEdge(int from, int to) override;

  [[nodiscard]] size_t VerticesCount() const override;

  [[nodiscard]] std::vector<int> GetChildren(int vertex) const override;

  [[nodiscard]] std::vector<int> GetParents(int vertex) const override;

 private:
  std::vector<std::vector<int>> _graph;
};

#endif  // MODULE3_TASK1_LISTGRAPH_HPP_
