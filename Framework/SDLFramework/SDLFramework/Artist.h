#pragma once
#include "IGameObject.h"
#include <SDL_render.h>
#include "Tile.h"
#include "Map.h"
#include "Globals.h"

class Artist : public IGameObject
{
public:
	Tile* currentTile;
	Map* map;
	SDL_Texture *texture;
	std::vector<Tile*> path;

	Artist(Map* mapIn);
	void move();
	~Artist();
	void Update(float deltaTime);

private:
	int actionTimer = 0;
};

