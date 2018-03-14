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

	std::vector<Tile*> neighbours;

	char type;
};

