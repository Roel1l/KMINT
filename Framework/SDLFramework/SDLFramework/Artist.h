#pragma once
#include "IGameObject.h"
#include <SDL_render.h>
#include "Tile.h"
#include "Map.h"

class Artist : public IGameObject
{
public:

	void Update(float deltaTime);

	Tile* currentTile;
	Map* map;

	SDL_Texture *texture;
	Artist(Map* mapIn);
	~Artist();
};

