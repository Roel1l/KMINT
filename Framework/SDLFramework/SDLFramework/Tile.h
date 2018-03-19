#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "FWApplication.h"
#include "Globals.h"

class Tile
{
public:
	Tile(char typeIn, int absoluteXIn, int absoluteYIn) { type = typeIn; absoluteX = absoluteXIn; absoluteY = absoluteYIn; }
	~Tile();

	int absoluteX;
	int absoluteY;

	int gridX() { return absoluteX / 20; }
	int gridY() { return absoluteY / 20; }

	double weight();
	bool traversable();

	double gCost = 0; //distance from starting node
	double hCost = 0; //distance from endnode

	double fCost() { return gCost + hCost; }

	Tile* parent;

	std::vector<Tile*> neighbours;

	Color color();
	bool partOfPath = false;

	char type;
};

