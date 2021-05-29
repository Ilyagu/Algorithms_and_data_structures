// Copyright 2021 Ilyagu Nagdimaev

#ifndef TASK1_IGRAPH_HPP
#define TASK1_IGRAPH_HPP

#include <vector>

struct IGraph {
	virtual ~IGraph() = default;

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) = 0;

	[[nodiscard]] virtual size_t VerticesCount() const  = 0;

	[[nodiscard]] virtual std::vector<int> GetNextVertices(int vertex) const = 0;
	[[nodiscard]] virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //TASK1_IGRAPH_HPP