// Copyright 2021 Ilyagu Nagdimaev

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

#include "arcGraph.hpp"
#include "listGraph.hpp"
#include "matrixGraph.hpp"
#include "setGraph.hpp"

void dfs_aux(const IGraph& graph, int vertex, std::vector<bool>& visited,
             std::function<void(int)>& callback, int& count) {
  visited[vertex] = true;
  callback(vertex);

  for (auto child : graph.GetChildren(vertex)) {
    if (!visited[child]) {
      count++;
      dfs_aux(graph, child, visited, callback, count);
    }
  }
}

void dfs(const IGraph& graph, std::function<void(int)> print) {
  std::vector<bool> visited;
  visited.resize(graph.VerticesCount(), false);

  int count = 0;

  for (int i = 0; i < graph.VerticesCount(); ++i) {
    if (!visited[i]) {
      count++;
      dfs_aux(graph, i, visited, print, count);
    }
  }
}

void bfs(const IGraph& graph, void (*callback)(int v)) {
  std::vector<bool> visited;
  std::queue<int> queue;
  visited.resize(graph.VerticesCount(), false);
  for (int i = 0; i < graph.VerticesCount(); ++i) {
    if (!visited[i]) {
      queue.push(i);
      visited[i] = true;
      while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        callback(vertex);
        for (auto child : graph.GetChildren(vertex)) {
          if (!visited[child]) {
            queue.push(child);
            visited[child] = true;
          }
        }
      }
    }
  }
}

int main() {
  ListGraph graph(7);

  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(1, 5);
  graph.AddEdge(2, 3);
  graph.AddEdge(3, 4);
  graph.AddEdge(4, 2);

  auto print = [](int v) { std::cout << v << " "; };

  std::cout << "------------------------" << std::endl;
  std::cout << "List Graph size = " << graph.VerticesCount() << std::endl;
  dfs(graph, print);

  std::cout << std::endl << "------------------------" << std::endl;
  MatrixGraph matrix_graph(graph);
  std::cout << "Matrix graph  size = " << matrix_graph.VerticesCount()
            << std::endl;

  dfs(matrix_graph, print);

  std::cout << std::endl << "------------------------" << std::endl;
  SetGraph set_graph(matrix_graph);
  std::cout << "Set graph  size = " << set_graph.VerticesCount() << std::endl;

  dfs(set_graph, print);

  std::cout << std::endl << "------------------------" << std::endl;
  ArcGraph arc_graph(set_graph);
  std::cout << "Arc graph  size = " << arc_graph.VerticesCount() << std::endl;

  dfs(arc_graph, print);

  std::cout << "\n";

  return 0;
}
