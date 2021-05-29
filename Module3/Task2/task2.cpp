// Copyright 2021 Ilyagu Nagdimaev

#include <vector>
#include <limits>
#include <queue>
#include <iostream>

struct IGraph {
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    [[nodiscard]] virtual int VerticesCount() const  = 0;

    [[nodiscard]] virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    [[nodiscard]] virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
 public:
    explicit ListGraph(size_t verticesCount);

    explicit ListGraph(const IGraph& graph);

    ~ListGraph() override = default;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    [[nodiscard]] int VerticesCount() const override;

    [[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

    [[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;

    [[nodiscard]] int short_paths(int from, int to) const;

 private:
    std::vector<std::vector<int>> graph_;
};

ListGraph::ListGraph(size_t verticesCount) : graph_(verticesCount) {}

ListGraph::ListGraph(const IGraph& graph) {
    for (int i = 0; i != graph.VerticesCount(); ++i) {
        graph_[i] = graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    graph_[from].push_back(to);

    graph_[to].push_back(from);
}

int ListGraph::VerticesCount() const {
    return graph_.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    return graph_[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_.size(); ++i) {
        for (auto child : graph_[i]) {
            if (child == vertex) {
                result.push_back(i);
                break;
            }
        }
    }
    return result;
}

int ListGraph::short_paths(int from, int to) const {
    std::vector<int> r(VerticesCount(),
                       std::numeric_limits<int>::max());
    std::vector<int> counter(VerticesCount(), 0);
    std::queue<int> q;
    q.push(from);

    r[from] = 0;
    counter[from] = 1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto w : GetNextVertices(v)) {
            if (r[w] > r[v] + 1) {
                r[w] = r[v] + 1;
                q.push(w);
                counter[w] = counter[v];
            } else if (r[w] == r[v] + 1) {
                counter[w] += counter[v];
            }
        }
    }
    return counter[to];
}


int main() {
    int vertices;
    std::cin >> vertices;
    ListGraph graph(vertices);
    int n;

    std::cin >> n;

    int ver1, ver2;
    for (size_t i = 0; i != n; ++i) {
        std::cin >> ver1 >> ver2;
        graph.AddEdge(ver1, ver2);
    }

    int from, to;
    std::cin >> from >> to;
    std::cout << graph.short_paths(from, to);


    return 0;
}
