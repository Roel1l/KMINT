#pragma once
#include <iostream>
#include <string>
#include <vector>

class Tile
{
public:
	Tile(char typeIn, int xIn, int yIn) { type = typeIn; absoluteX = xIn; absoluteY = yIn; }
	~Tile();

	int absoluteX;
	int absoluteY;

	int gridX() { return absoluteX / 20; }
	int gridY() { return absoluteY / 20; }

	double weight;

	double gCost = 0; //distance from starting node
	double hCost = 0; //distance from endnode

	double fCost() { return gCost + hCost; }

	Tile* parent;

	std::vector<Tile*> neighbours;

	char type;
};

