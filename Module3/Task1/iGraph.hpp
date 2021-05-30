// Copyright 2021 Ilyagu Nagdimaev

#ifndef MODULE3_TASK1_IGRAPH_HPP_
#define MODULE3_TASK1_IGRAPH_HPP_

#include <vector>

struct IGraph {
  virtual ~IGraph() = default;

  // Добавление ребра от from к to.
  virtual void AddEdge(int from, int to) = 0;

  [[nodiscard]] virtual size_t VerticesCount() const = 0;

  [[nodiscard]] virtual std::vector<int> GetNextVertices(int vertex) const = 0;
  [[nodiscard]] virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif  // MODULE3_TASK1_IGRAPH_HPP_
