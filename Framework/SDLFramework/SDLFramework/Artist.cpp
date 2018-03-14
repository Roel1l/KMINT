#include "Artist.h"

void Artist::Update(float deltaTime)
{
	if (GLOBAL_ACTION_TIMER == 0 || GLOBAL_ACTION_TIMER == GLOBAL_SPEED / 2) {
		move();
	}

	mApplication->SetColor(Color(0, 0, 102, 255));
	mApplication->DrawCircle(currentTile->absoluteX + 10, currentTile->absoluteY + 10, 10, true);
}


Artist::Artist(Map * mapIn)
{
	map = mapIn; 
	currentTile = map->getTile(4, 7);
}

void Artist::move() {
	if (path.size() > 0) {
		currentTile = path[0];
		path.erase(path.begin());
	}
	else {
		Tile* target = map->getTile(generateRandom(0, map->xMax), generateRandom(0, map->yMax));
		path = map->findPath(currentTile, target);
	}
}

Artist::~Artist()
{
}
