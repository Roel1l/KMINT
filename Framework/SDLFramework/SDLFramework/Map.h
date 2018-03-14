#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Math.h"
#include "Tile.h"
#include "FWApplication.h"

class Map
{
public:
	Map();
	~Map();
	void loadMap();

	Tile * getTile(int x, int y);

	void initTileNeighbours();

	int xMax = 0; //Zero-based
	int yMax = 0; //Zero-based

	void drawMap(FWApplication * application);

	std::vector<Tile*> findPath(Tile * start, Tile * target);

	double getDistance(Tile * A, Tile * B);

	std::vector<std::vector<Tile*>> grid;
};

