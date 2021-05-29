// Copyright 2021 Ilyagu Nagdimaev

#ifndef TASK1_ARCGRAPH_HPP
#define TASK1_ARCGRAPH_HPP

#include <utility>
#include <vector>

#include "iGraph.hpp"

class ArcGraph : public IGraph {
public:

	explicit ArcGraph(size_t verticesCount);

	explicit ArcGraph(const IGraph& graph);

	void AddEdge(int from, int to) override;


	[[nodiscard]] size_t VerticesCount() const override;

	[[nodiscard]] std::vector<int> GetNextVertices(int vertex) const  override;

	[[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;


private:
	std::vector<std::pair<int, int>> _graph;
};

#endif //TASK1_ARCGRAPH_HPP