// Copyright 2021 Ilyagu Nagdimaev

#include <cassert>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

struct IWeightGraph {
  virtual ~IWeightGraph() = default;

  // Добавление ребра от from к to.
  virtual void AddEdge(int from, int to, int weight) = 0;

  [[nodiscard]] virtual int VerticesCount() const = 0;

  [[nodiscard]] virtual std::vector<std::pair<int, int>>
    GetChildren(int vertex) const = 0;
  [[nodiscard]] virtual std::vector<std::pair<int, int>>
    GetParents(int vertex) const = 0;
};

class WeightListGraph : public IWeightGraph {
 public:
  explicit WeightListGraph(int vertexCount);
  explicit WeightListGraph(const IWeightGraph& graph);

  void AddEdge(int from, int to, int weight) override;

  [[nodiscard]] int VerticesCount() const override;
  [[nodiscard]] std::vector<std::pair<int, int>>
    GetChildren(int vertex) const override; // вершина, вес
  [[nodiscard]] std::vector<std::pair<int, int>>
    GetParents(int vertex) const override; // вершина, вес

 private:
  std::vector<std::vector<std::pair<int, int>>>
      adjacencyLists; // вершина, вес
};

WeightListGraph::WeightListGraph(int vertexCount)
    : adjacencyLists(vertexCount) {}

WeightListGraph::WeightListGraph(const IWeightGraph& graph) {
  adjacencyLists.resize(graph.VerticesCount());
  for (int from = 0; from < adjacencyLists.size(); from++)
    adjacencyLists[from] = graph.GetChildren(from);
}

void WeightListGraph::AddEdge(int from, int to, int weight) {
  assert(from >= 0 && from < adjacencyLists.size());
  assert(to >= 0 && to < adjacencyLists.size());
  assert(weight >= 0);

  adjacencyLists[from].push_back(std::make_pair(to, weight));
  adjacencyLists[to].push_back(std::make_pair(from, weight));
  // добавлено чтобы граф был неориентированным
}

int WeightListGraph::VerticesCount() const {
  return adjacencyLists.size();
}

std::vector<std::pair<int, int>> WeightListGraph::GetChildren(
    int vertex) const {
  assert(vertex >= 0 && vertex < adjacencyLists.size());
  return adjacencyLists[vertex];
}

std::vector<std::pair<int, int>> WeightListGraph::GetParents(int vertex) const {
  assert(vertex >= 0 && vertex < adjacencyLists.size());
  std::vector<std::pair<int, int>> result;
  for (int from = 0; from < adjacencyLists.size(); from++)
    for (int i = 0; i < adjacencyLists[from].size(); i++)
      if (adjacencyLists[from][i].first == vertex)
        result.emplace_back(from, adjacencyLists[from][i].second);
  return result;
}

int Relax(std::vector<int>& wayMinWeights, int EdgeWeight, int from,
          int to, std::vector<int>& parents) {
  if (wayMinWeights[to] > wayMinWeights[from] + EdgeWeight) {
    int oldWeight = wayMinWeights[to];
    wayMinWeights[to] = wayMinWeights[from] + EdgeWeight;
    parents[to] = from;
    return oldWeight;
  }
  return -1;
}

int minWay(const IWeightGraph& graph, int from, int to) {
  std::vector<int> parents(graph.VerticesCount(), -1);
  std::vector<int> wayMinWeights(graph.VerticesCount(),
                                  std::numeric_limits<int>::max());

  auto comp = [](std::pair<int, int> w1, std::pair<int, int> w2) {
    if (w1.second < w2.second)
      return true;
    else if (w1.second > w2.second)
      return false;
    else
      return w1.first < w2.first;
  };

  std::set<std::pair<int, int>, decltype(comp)> priorityQueue(comp);

  wayMinWeights[from] = 0;
  priorityQueue.insert(std::make_pair(from, wayMinWeights[from]));

  while (!priorityQueue.empty()) {
    auto cur = priorityQueue.begin();
    std::pair<int, int> current = *cur;
    priorityQueue.erase(cur);
    auto children = graph.GetChildren(current.first);
    for (int i = 0; i < children.size(); i++) {
      // встречаем вершину первый раз - задаем текущий путь
      if (wayMinWeights[children[i].first] ==
          std::numeric_limits<int>::max()) {
        wayMinWeights[children[i].first] =
            wayMinWeights[current.first] + children[i].second;
        parents[children[i].first] = current.first;
        priorityQueue.insert(std::make_pair(
            children[i].first, wayMinWeights[children[i].first]));
        // уже встречали вершину - пробуем оптимизировать путь с помощью Relax
      } else {
        int oldWeight = Relax(wayMinWeights, children[i].second,
                              current.first, children[i].first, parents);
        if (oldWeight != -1) {
          // заменяем элемент в очереди уже с актуальным весом пути
          auto element = priorityQueue.find(
              std::make_pair(children[i].first, oldWeight));
          if (element != priorityQueue.end()) priorityQueue.erase(element);
          priorityQueue.insert(
              std::make_pair(children[i].first, wayMinWeights[i]));
        }
      }
    }
  }

  return wayMinWeights[to];
}

int main() {
  int vertices = 0;
  std::cin >> vertices;

  WeightListGraph weightListGraph(vertices);

  int edges = 0, from = 0, to = 0;
  std::cin >> edges;

  for (int i = 0; i < edges; i++) {
    int weight = 0;
    std::cin >> from >> to >> weight;
    weightListGraph.AddEdge(from, to, weight);
  }

  std::cin >> from >> to;

  std::cout << minWay(weightListGraph, from, to) << std::endl;
  return 0;
}
