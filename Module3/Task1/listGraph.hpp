// Copyright 2021 Ilyagu Nagdimaev

#ifndef TASK1_LISTGRAPH_HPP
#define TASK1_LISTGRAPH_HPP

#include <vector>

#include "iGraph.hpp"

class ListGraph : public IGraph {
public:
	explicit ListGraph(size_t verticesCount);

	explicit ListGraph(const IGraph& graph);

	~ListGraph() override = default;

	// Добавление ребра от from к to.
	void AddEdge(int from, int to) override;

	[[nodiscard]] size_t VerticesCount() const override;

	[[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

	[[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;

private:
	std::vector<std::vector<int> > _graph;
};

#endif //TASK1_LISTGRAPH_HPP