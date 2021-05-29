// Copyright 2021 Ilyagu Nagdimaev

#include <cassert>
#include <iostream>
#include <set>
#include <vector>

#define MAX_INT32 2147483647

struct IWeightGraph {
  virtual ~IWeightGraph() = default;

  // Добавление ребра от from к to.
  virtual void AddEdge(int from, int to, int weight) = 0;

  [[nodiscard]] virtual int VerticesCount() const = 0;

  [[nodiscard]] virtual std::vector<std::pair<int, int>> GetNextVertices(
      int vertex) const = 0;
  [[nodiscard]] virtual std::vector<std::pair<int, int>> GetPrevVertices(
      int vertex) const = 0;
};

class WeightListGraph : public IWeightGraph {
 public:
  explicit WeightListGraph(int vertexCount);
  explicit WeightListGraph(const IWeightGraph& graph);

  void AddEdge(int from, int to, int weight) override;

  [[nodiscard]] int VerticesCount() const override;
  [[nodiscard]] std::vector<std::pair<int, int>> GetNextVertices(
      int vertex) const override;  // vertex, weight
  [[nodiscard]] std::vector<std::pair<int, int>> GetPrevVertices(
      int vertex) const override;  // vertex, weight

 private:
  std::vector<std::vector<std::pair<int, int>>>
      adjacencyLists;  // vertex, weight
};

WeightListGraph::WeightListGraph(int vertexCount)
    : adjacencyLists(vertexCount) {}

WeightListGraph::WeightListGraph(const IWeightGraph& graph) {
  adjacencyLists.resize(graph.VerticesCount());
  for (int from = 0; from < adjacencyLists.size(); ++from)
    adjacencyLists[from] = graph.GetNextVertices(from);
}

void WeightListGraph::AddEdge(int from, int to, int weight) {
  assert(from >= 0 && from < adjacencyLists.size());
  assert(to >= 0 && to < adjacencyLists.size());
  assert(weight >= 0);

  adjacencyLists[from].push_back(std::make_pair(to, weight));
  adjacencyLists[to].push_back(std::make_pair(
      from, weight));  // добавлено чтобы граф был неориентированным
}

int WeightListGraph::VerticesCount() const { return adjacencyLists.size(); }

std::vector<std::pair<int, int>> WeightListGraph::GetNextVertices(
    int vertex) const {
  assert(vertex >= 0 && vertex < adjacencyLists.size());
  return adjacencyLists[vertex];
}

std::vector<std::pair<int, int>> WeightListGraph::GetPrevVertices(
    int vertex) const {
  assert(vertex >= 0 && vertex < adjacencyLists.size());
  std::vector<std::pair<int, int>> result;
  for (int from = 0; from < adjacencyLists.size(); ++from)
    for (int i = 0; i < adjacencyLists[from].size(); ++i)
      if (adjacencyLists[from][i].first == vertex)
        result.emplace_back(from, adjacencyLists[from][i].second);
  return result;
}

int Relax(std::vector<int>& pathMinWeights, int fromToEdgeWeight, int from,
          int to, std::vector<int>& parents) {
  if (pathMinWeights[to] > pathMinWeights[from] + fromToEdgeWeight) {
    int oldWeight = pathMinWeights[to];
    pathMinWeights[to] = pathMinWeights[from] + fromToEdgeWeight;
    parents[to] = from;
    return oldWeight;
  }
  return -1;
}

int minPath(const IWeightGraph& graph, int from, int to) {
  std::vector<int> parents(graph.VerticesCount(), -1);
  std::vector<int> pathMinWeights(graph.VerticesCount(), MAX_INT32);

  auto cmp = [](std::pair<int, int> p1, std::pair<int, int> p2) {
    if (p1.second < p2.second)
      return true;
    else if (p1.second > p2.second)
      return false;
    else
      return p1.first < p2.first;
  };
  std::set<std::pair<int, int>, decltype(cmp)> priorityQueue(cmp);

  pathMinWeights[from] = 0;
  priorityQueue.insert(std::make_pair(from, pathMinWeights[from]));

  while (!priorityQueue.empty()) {
    auto cur = priorityQueue.begin();
    std::pair<int, int> current = *cur;
    priorityQueue.erase(cur);
    auto nextVertices = graph.GetNextVertices(current.first);
    for (int i = 0; i < nextVertices.size(); i++) {
      // встречаем вершину первый раз - задаем текущий путь
      if (pathMinWeights[nextVertices[i].first] == MAX_INT32) {
        pathMinWeights[nextVertices[i].first] =
            pathMinWeights[current.first] + nextVertices[i].second;
        parents[nextVertices[i].first] = current.first;
        priorityQueue.insert(std::make_pair(
            nextVertices[i].first, pathMinWeights[nextVertices[i].first]));
        // уже встречали вершину - пробуем оптимизировать путь с помощью Relax
      } else {
        int oldWeight = Relax(pathMinWeights, nextVertices[i].second,
                              current.first, nextVertices[i].first, parents);
        if (oldWeight != -1) {
          // заменяем элемент в очереди уже с актуальным весом пути
          auto element = priorityQueue.find(
              std::make_pair(nextVertices[i].first, oldWeight));
          if (element != priorityQueue.end()) priorityQueue.erase(element);
          priorityQueue.insert(
              std::make_pair(nextVertices[i].first, pathMinWeights[i]));
        }
      }
    }
  }

  return pathMinWeights[to];
}

int main() {
  int n = 0;
  std::cin >> n;

  WeightListGraph graph(n);

  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    int from;
    int to;
    int weight;
    std::cin >> from >> to >> weight;
    graph.AddEdge(from, to, weight);
  }

  int from = 0;
  int to = 0;
  std::cin >> from >> to;

  std::cout << minPath(graph, from, to);
  return 0;
}
