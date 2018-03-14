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

	int x = 0;

	while (std::getline(infile, line)) {
		if (line.length() > 0) {
			std::vector<Tile*> s;
			grid.push_back(s);

			for (int y = 0; y < line.length(); y++)
			{
				grid[x].push_back(new Tile(line[y], x * 20, y * 20));
			}

			x++;
		}
	}

	xMax = grid.size() - 1;
	yMax = grid[0].size() - 1;

	infile.close();
}

Tile* Map::getTile(int x, int y) {
	return grid[x][y];
}

void Map::initTileNeighbours() {
	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[x].size(); y++)
		{
			if(x > 0) grid[x][y]->neighbours.push_back(grid[x - 1][y]); //Links
			if(x < grid.size() - 1) grid[x][y]->neighbours.push_back(grid[x + 1][y]); //Rechts
			if (y < grid[x].size() - 1) grid[x][y]->neighbours.push_back(grid[x][y + 1]); //Onder
			if (y > 0) grid[x][y]->neighbours.push_back(grid[x][y - 1]); //Boven
		}
	}
}

void Map::drawMap(FWApplication* application) {
	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[y].size(); x++)
		{
			switch (grid[y][x]->type) {
			case 'B': application->SetColor(Color(47, 79, 79, 255)); break;
			case '1': application->SetColor(Color(211, 211, 211, 255)); break;
			case '2': application->SetColor(Color(149, 143, 121, 255)); break;
			case '3': application->SetColor(Color(141, 0, 0, 255)); break;
			case 'L': application->SetColor(Color(153, 0, 0, 255)); break;
			case 'N': application->SetColor(Color(0, 128, 0, 255)); break;
			case 'P': application->SetColor(Color(0, 0, 255, 255)); break;
			case 'C': application->SetColor(Color(128, 0, 128, 255)); break;
			default: application->SetColor(Color(0, 0, 0, 255)); break;
			}

			application->DrawRect(x * 20, y * 20, 20, 20, true);
		}
	}
}

std::vector<Tile*> Map::findPath(Tile* start, Tile* target) {
	std::vector<Tile*> openSet;
	std::vector<Tile*> closedSet;

	openSet.push_back(start);

	while (openSet.size() > 0) {
		Tile* current = openSet[0];
		for each (Tile* t in openSet) {
			if (t->fCost() < current->fCost() || t->fCost() == current->fCost() && t->hCost < current->hCost) current = t;
		}

		openSet.erase(std::remove(openSet.begin(), openSet.end(), current), openSet.end());
		closedSet.push_back(current);

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
			if (std::find(closedSet.begin(), closedSet.end(), neighbour) != closedSet.end()) {
				continue;
			}

			double newMovementCostToNeighbour = current->gCost + getDistance(current, neighbour);
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