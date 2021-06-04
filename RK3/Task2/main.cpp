// Copyright 2021 Ilyagu Nagdimaev

#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <functional>

struct IGraph {
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetChildren(int vertex) const = 0;

    virtual std::vector<int> GetParents(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    explicit ListGraph(size_t verticesCount);

    explicit ListGraph(const IGraph &graph);

    ~ListGraph() override = default;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetChildren(int vertex) const override;

    std::vector<int> GetParents(int vertex) const override;

private:
    std::vector<std::vector<int>> _graph;
};

ListGraph::ListGraph(size_t verticesCount) : _graph(verticesCount) {}

ListGraph::ListGraph(const IGraph &graph) {
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

void dfs_aux(const IGraph& graph, int vertex, std::vector<bool>& visited) {
    visited[vertex] = true;

    for (auto child : graph.GetChildren(vertex)) {
        if (!visited[child]) {
            dfs_aux(graph, child, visited);
        }
    }
}

int dfs(const IGraph& graph) {
    std::vector<bool> visited;
    visited.resize(graph.VerticesCount(), false);

    int count = 0;

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            dfs_aux(graph, i, visited);
            count++;
        }
    }
    return count;
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

    std::cout << dfs(listGraph) << std::endl;

    return 0;
}
