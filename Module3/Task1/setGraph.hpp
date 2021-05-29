// Copyright 2021 Ilyagu Nagdimaev

#ifndef TASK1_SETGRAPH_HPP
#define TASK1_SETGRAPH_HPP

#include <set>
#include <vector>

#include "iGraph.hpp"

class SetGraph : public IGraph {
public:

	explicit SetGraph(size_t verticesCount);

	explicit SetGraph(const IGraph& graph);

	void AddEdge(int from, int to) override;


	[[nodiscard]] size_t VerticesCount() const override;

	[[nodiscard]] std::vector<int> GetNextVertices(int vertex) const override;

	[[nodiscard]] std::vector<int> GetPrevVertices(int vertex) const override;


private:
	std::vector<std::set<int>> _graph;
};

#endif //TASK1_SETGRAPH_HPP