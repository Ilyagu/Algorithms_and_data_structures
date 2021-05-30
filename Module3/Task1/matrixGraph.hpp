// Copyright 2021 Ilyagu Nagdimaev

#ifndef MODULE3_TASK1_MATRIXGRAPH_HPP_
#define MODULE3_TASK1_MATRIXGRAPH_HPP_

#include <vector>

#include "iGraph.hpp"

class MatrixGraph : public IGraph {
 public:
  explicit MatrixGraph(size_t verticesCount);

  explicit MatrixGraph(const IGraph& imageGraph);

  void AddEdge(int from, int to) override;

  [[nodiscard]] size_t VerticesCount() const override;

  [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

  [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  std::vector<std::vector<int>> _graph;
};

#endif  // MODULE3_TASK1_MATRIXGRAPH_HPP_
