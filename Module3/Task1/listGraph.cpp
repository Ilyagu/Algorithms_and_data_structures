// Copyright 2021 Ilyagu Nagdimaev

#include "listGraph.hpp"

ListGraph::ListGraph(size_t verticesCount) : _graph(verticesCount) {}

ListGraph::ListGraph(const IGraph &imageGraph) {
  for (int i = 0; i != imageGraph.VerticesCount(); ++i) {
    _graph[i] = imageGraph.GetChildren(i);
  }
}

void ListGraph::AddEdge(int from, int to) { _graph[from].push_back(to); }

size_t ListGraph::VerticesCount() const { return _graph.size(); }

std::vector<int> ListGraph::GetChildren(int vertex) const {
  std::vector<int> result;
  result.resize(_graph[vertex].size());
  std::copy(_graph[vertex].begin(), _graph[vertex].end(), result.begin());
  return result;
}

std::vector<int> ListGraph::GetParents(int vertex) const {
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
