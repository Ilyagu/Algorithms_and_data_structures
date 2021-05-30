// Copyright 2021 Ilyagu Nagdimaev

#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct IGraph {
  virtual ~IGraph() = default;

  // Добавление ребра от from к to.
  virtual void AddEdge(int from, int to) = 0;

  [[nodiscard]] virtual int VerticesCount() const = 0;

  [[nodiscard]] virtual std::vector<int> GetChildren(int vertex) const = 0;
  [[nodiscard]] virtual std::vector<int> GetParents(int vertex) const = 0;
};

class ListGraph : public IGraph {
 public:
  explicit ListGraph(size_t verticesCount);

  explicit ListGraph(const IGraph& graph);

  ~ListGraph() override = default;

  // Добавление ребра от from к to.
  void AddEdge(int from, int to) override;

  [[nodiscard]] int VerticesCount() const override;

  [[nodiscard]] std::vector<int> GetChildren(int vertex) const override;

  [[nodiscard]] std::vector<int> GetParents(int vertex) const override;

  [[nodiscard]] int minWay(int from, int to) const;

 private:
  std::vector<std::vector<int>> _graph;
};

ListGraph::ListGraph(size_t verticesCount) : _graph(verticesCount) {}

ListGraph::ListGraph(const IGraph& graph) {
  for (int i = 0; i != graph.VerticesCount(); i++) {
    _graph[i] = graph.GetChildren(i);
  }
}

void ListGraph::AddEdge(int from, int to) {
  _graph[from].push_back(to);

  _graph[to].push_back(from);
}

int ListGraph::VerticesCount() const { return _graph.size(); }

std::vector<int> ListGraph::GetChildren(int vertex) const {
  std::vector<int> result;
  result.resize(_graph[vertex].size());
  std::copy(_graph[vertex].begin(), _graph[vertex].end(), result.begin());
  return result;
}

std::vector<int> ListGraph::GetParents(int vertex) const {
  std::vector<int> result;
  for (int i = 0; i < _graph.size(); i++) {
    for (auto child : _graph[i]) {
      if (child == vertex) {
        result.push_back(i);
        break;
      }
    }
  }
  return result;
}

int ListGraph::minWay(int from, int to) const {
  std::vector<int> lol(VerticesCount(), std::numeric_limits<int>::max());
  std::vector<int> minWaysCounter(VerticesCount(), 0);
  std::queue<int> queue;
  queue.push(from);

  lol[from] = 0;
  minWaysCounter[from] = 1;

  while (!queue.empty()) {
    int vertex = queue.front();
    queue.pop();

    for (auto child : GetChildren(vertex)) {
      if (lol[child] > lol[vertex] + 1) {
        lol[child] = lol[vertex] + 1;
        queue.push(child);
        minWaysCounter[child] = minWaysCounter[vertex];
      } else if (lol[child] == lol[vertex] + 1) {
        minWaysCounter[child] += minWaysCounter[vertex];
      }
    }
  }
  return minWaysCounter[to];
}

int main() {
  int vertices = 0;
  std::cin >> vertices;

  ListGraph listGraph(vertices);

  int edges = 0;
  std::cin >> edges;

  int from = 0, to = 0;
  for (size_t i = 0; i != edges; i++) {
    std::cin >> from >> to;
    listGraph.AddEdge(from, to);
  }

  std::cin >> from >> to;
  std::cout << listGraph.minWay(from, to) << std::endl;

  return 0;
}
