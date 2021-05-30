// Copyright 2021 Ilyagu Nagdimaev

#include "arcGraph.hpp"

ArcGraph::ArcGraph(size_t verticesCount) : _graph(verticesCount) {}

ArcGraph::ArcGraph(const IGraph &imageGraph) {
  for (int i = 0; i != imageGraph.VerticesCount(); ++i) {
    std::vector<int> children = imageGraph.GetChildren(i);
    for (int child : children) {
      _graph.emplace_back(std::make_pair(i, child));
    }
  }
}

void ArcGraph::AddEdge(int from, int to) {
  _graph.emplace_back(std::make_pair(from, to));
}

size_t ArcGraph::VerticesCount() const { return _graph.size(); }

std::vector<int> ArcGraph::GetChildren(int vertex) const {
  std::vector<int> result;

  for (auto &edge : _graph) {
    if (edge.first == vertex) result.push_back(edge.second);
  }

  return result;
}

std::vector<int> ArcGraph::GetParents(int vertex) const {
  std::vector<int> result;

  for (auto &edge : _graph) {
    if (edge.second == vertex) result.push_back(edge.first);
  }

  return result;
}
