// Copyright 2021 Ilyagu Nagdimaev

#include "listGraph.hpp"

ListGraph::ListGraph(size_t verticesCount) : _graph(verticesCount) {}

ListGraph::ListGraph(const IGraph &graph) {
  for (int i = 0; i != graph.VerticesCount(); ++i) {
    _graph[i] = graph.GetNextVertices(i);
  }
}

void ListGraph::AddEdge(int from, int to) { _graph[from].push_back(to); }

size_t ListGraph::VerticesCount() const { return _graph.size(); }

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
  return _graph[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
  std::vector<int> result;
  for (int i = 0; i < _graph.size(); ++i) {
    for (auto child : _graph[i]) {
      if (child == vertex) {
        result.push_back(i);
        break;
      }
    }
  }
  return result;
}
