#pragma once
#include <vector>
#include <tuple>

class Vertex
{
public:
	double x;
	double y;
	double weight;

	double gCost = 0;
	double hCost = 0;

	double fCost() { return gCost + hCost; }

	Vertex* parent;

	Vertex();
	Vertex(double xIn, double yIn);
	~Vertex();

	std::vector<Vertex*> edges;

};

