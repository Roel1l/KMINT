#pragma once
#include "IGameObject.h"
#include <SDL_render.h>
#include "Tile.h"
#include "Map.h"
#include "Globals.h"
#include "ArtistState.h"


class ArtistState;

class Artist : public IGameObject
{
public:
	Tile* currentTile;
	Map* map;
	SDL_Texture *texture;
	std::vector<Tile*> path;
	ArtistState* state;
	Color color = Color(0, 0, 102, 255);

	int money = 1000;
	int wait = 0;
	uint32_t msTimeBetweenActions = 1000; //Means the artist will execute an action every 1000 ms
	uint32_t msTimeOfLastAction = 0;

	Artist(Map* mapIn);
	void setColor(Color colorIn) { color = colorIn; }
	void move();
	void changeState(ArtistState* stateIn) { state = stateIn; }
	~Artist();
	void Update(float deltaTime);

private:
	int actionTimer = 0;
};

