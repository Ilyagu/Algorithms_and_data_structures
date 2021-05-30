// Copyright 2021 Ilyagu Nagdimaev

#include "matrixGraph.hpp"

MatrixGraph::MatrixGraph(size_t verticesCount)
    : _graph(verticesCount, std::vector<int>(verticesCount, 0)) {}

MatrixGraph::MatrixGraph(const IGraph &imageGraph)
    : _graph(imageGraph.VerticesCount(),
             std::vector<int>(imageGraph.VerticesCount(), 0)) {
  for (int i = 0; i != imageGraph.VerticesCount(); ++i) {
    std::vector<int> verticals = imageGraph.GetChildren(i);
    for (int elem : verticals) {
      _graph[i][elem] = 1;
    }
  }
}

void MatrixGraph::AddEdge(int from, int to) { _graph[from][to] = 1; }

size_t MatrixGraph::VerticesCount() const { return _graph.size(); }

std::vector<int> MatrixGraph::GetChildren(int vertex) const {
  std::vector<int> result;

  for (int i = 0; i != _graph[vertex].size(); ++i) {
    if (_graph[vertex][i] == 1) result.push_back(i);
  }
  return result;
}

std::vector<int> MatrixGraph::GetParents(int vertex) const {
  std::vector<int> result;

  for (int i = 0; i != _graph.size(); ++i) {
    if (_graph[i][vertex] == 1) result.push_back(i);
  }
  return result;
}
