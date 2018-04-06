#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
	for each (std::vector<Tile*> row in grid)
	{
		for each (Tile* tile in row)
		{
			delete tile;
		}
	}
}

void Map::loadMap() {
	std::ifstream infile("../Resources/map.txt");
	std::string line;

	yMax = std::count(std::istreambuf_iterator<char>(infile),
		std::istreambuf_iterator<char>(), '\n') - 1;

	infile.clear();
	infile.seekg(0, std::ios::beg);

	int counter = 0;

	while (std::getline(infile, line)) {
		if (line.length() > 0 && xMax < 1) {
			xMax = line.length();
			grid = std::vector<std::vector<Tile*>>(xMax);
			for (int i = 0; i < grid.size(); i++) grid[i] = std::vector<Tile*>(yMax);
		}
		if (line.length() > 0) {
			
			for (int i = 0; i < line.length(); i++) grid[i][counter] = new Tile(line[i], i * 20, counter * 20);
			

			counter++;
		}
	}

	infile.close();

	for (int x = 0; x < xMax; x++)
	{
		for (int y = 0; y < yMax; y++)
		{
			char tileType = grid[x][y]->type;
			if (tileType == 'B') solidTileIndexes.push_back(std::tuple<int, int>{ x, y });
			else if(tileType == '1' || tileType == '2' || tileType == '3') walkableTileIndexes.push_back(std::tuple<int, int>{ x, y });
			else shopTileIndexes.push_back(std::tuple<int, int>{ x, y });
		}
	}
}

Tile* Map::getTile(int x, int y) {
	return grid[x][y];
}

Tile* Map::getTileByCoordinates(double xIn, double yIn) {

	int x = xIn / 20;
	int y = yIn / 20;

	if(x < xMax && y < yMax)
	return grid[x][y];
	else return grid[0][0];
}

void Map::initTileNeighbours() {
	for (int x = 0; x < xMax; x++)
	{
		for (int y = 0; y < yMax; y++)
		{
			if(x > 0) grid[x][y]->neighbours.push_back(grid[x - 1][y]); //Links
			if(x < xMax - 1) grid[x][y]->neighbours.push_back(grid[x + 1][y]); //Rechts
			if (y < yMax - 1) grid[x][y]->neighbours.push_back(grid[x][y + 1]); //Onder
			if (y > 0) grid[x][y]->neighbours.push_back(grid[x][y - 1]); //Boven
		}
	}
}

void Map::drawMap(FWApplication* application) {
	for (int x = 0; x < xMax; x++)
	{
		for (int y = 0; y < yMax; y++)
		{
			application->SetColor(grid[x][y]->color());
			application->DrawRect(x * 20, y * 20, 20, 20, true);
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Uses the A* algorithm to find a path of tiles from a starting tile to a finish tile. (https://youtu.be/mZfyt03LDH4) </summary>
///
/// <remarks>	Roel Guerand, 14-03-2018. </remarks>
///
/// <returns>	A list of tiles that represent the shortest path from the given start to the given target </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Tile*> Map::findPath(Tile* start, Tile* target) {
	std::vector<Tile*> openSet;
	std::vector<Tile*> closedSet;

	openSet.push_back(start);

	while (openSet.size() > 0) {
		Tile* current = openSet[0];
		for each (Tile* t in openSet) {
			// Check which tile seems cheapest to travel through.
			if (t->fCost() < current->fCost() || t->fCost() == current->fCost() && t->hCost < current->hCost) current = t;
		}

		openSet.erase(std::remove(openSet.begin(), openSet.end(), current), openSet.end());
		closedSet.push_back(current);

		// If current is the target node path has been found
		if (current == target) {
			std::vector<Tile*> path;
			Tile* t = target;

			while (t != start) {
				path.push_back(t);
				t = t->parent;
			}

			std::reverse(path.begin(), path.end());
			return path;
		}

		for each (Tile* neighbour in current->neighbours) {
			// If the neighbour was checked already or if it's not possible to walk to the neighbour continue the loop
			if (std::find(closedSet.begin(), closedSet.end(), neighbour) != closedSet.end() || !neighbour->traversable()) {
				continue;
			}

			// Calculate the cost of walking to the neigbour taking the neighbours weight in account.
			double newMovementCostToNeighbour = current->gCost + getDistance(current, neighbour) * neighbour->weight();
			if (newMovementCostToNeighbour < neighbour->gCost || std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end()) {
				neighbour->gCost = newMovementCostToNeighbour;
				neighbour->hCost = getDistance(neighbour, target);
				neighbour->parent = current;

				if (std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end()) {
					openSet.push_back(neighbour);
				}
			}

		}

	}
}

double Map::getDistance(Tile* A, Tile* B) {

	double distX = fabs(A->gridX() - B->gridX());
	double distY = fabs(A->gridY() - B->gridY());

	if (distX > distY) return 14 * distY + 10 * (distX - distY);
	else return 14 * distX + 10 * (distY - distX);
}