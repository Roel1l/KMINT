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

	Tile * getTileByCoordinates(double x, double y);

	void initTileNeighbours();

	int xMax = 0; //Zero-based
	int yMax = 0; //Zero-based

	void drawMap(FWApplication * application);

	std::vector<Tile*> findPath(Tile * start, Tile * target);
	std::vector<Tile*> visitedByAlgorithm;

	double getDistance(Tile * A, Tile * B);

	void clearAlgorithmTiles();

	std::vector<std::vector<Tile*>> grid;

	std::vector<std::tuple<int, int>> walkableTileIndexes;
	std::vector<std::tuple<int, int>> shopTileIndexes;
	std::vector<std::tuple<int, int>> solidTileIndexes;

	bool keepTrackOfAlgorithm = false;
};

