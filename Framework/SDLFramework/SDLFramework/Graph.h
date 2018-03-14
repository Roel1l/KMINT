#pragma once
#include "Vertex.h"
#include <vector>
#include <tuple>

class Graph
{
public:
	Graph();
	void init();
	void addVertex(Vertex * v);
	void addEdge(Vertex * from, Vertex * to, int weight);

	std::vector<Vertex*> findPath(Vertex * start, Vertex * target);

	double getDistance(Vertex * A, Vertex * B);

	~Graph();

	std::vector<Vertex*> vertices;
};

