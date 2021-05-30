// Copyright 2021 Ilyagu Nagdimaev

#include "setGraph.hpp"

SetGraph::SetGraph(size_t verticesCount) : _graph(verticesCount) {}

SetGraph::SetGraph(const IGraph &imageGraph) {
  _graph.resize(imageGraph.VerticesCount());
  for (int i = 0; i != imageGraph.VerticesCount(); ++i) {
    std::vector<int> vertices = imageGraph.GetChildren(i);
    _graph[i].insert(vertices.begin(), vertices.end());
  }
}

void SetGraph::AddEdge(int from, int to) { _graph[from].insert(to); }

size_t SetGraph::VerticesCount() const { return _graph.size(); }

std::vector<int> SetGraph::GetChildren(int vertex) const {
  std::vector<int> result;

  for (int vertical : _graph[vertex]) result.push_back(vertical);
  return result;
}

std::vector<int> SetGraph::GetParents(int vertex) const {
  std::vector<int> result;
  for (int i = 0; i < _graph.size(); ++i) {
    for (int child : _graph[i]) {
      if (child == vertex) {
        result.push_back(i);
        break;
      }
    }
  }
  return result;
}
