// Copyright 2021 Ilyagu Nagdimaev

#include "arcGraph.hpp"

ArcGraph::ArcGraph(size_t verticesCount) : _graph(verticesCount) {}

ArcGraph::ArcGraph(const IGraph &graph) {
  for (int i = 0; i != graph.VerticesCount(); ++i) {
    std::vector<int> vertices = graph.GetNextVertices(i);
    for (int elem : vertices) {
      _graph.emplace_back(std::make_pair(i, elem));
    }
  }
}

void ArcGraph::AddEdge(int from, int to) {
  _graph.emplace_back(std::make_pair(from, to));
}

size_t ArcGraph::VerticesCount() const { return _graph.size(); }

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
  std::vector<int> result;

  for (auto &edge : _graph) {
    if (edge.first == vertex) result.push_back(edge.second);
  }

  return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
  std::vector<int> result;

  for (auto &edge : _graph) {
    if (edge.second == vertex) result.push_back(edge.first);
  }

  return result;
}
