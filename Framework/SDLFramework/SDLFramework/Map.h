#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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


	void drawMap(FWApplication * application);

	std::vector<std::vector<Tile*>> grid;
};

