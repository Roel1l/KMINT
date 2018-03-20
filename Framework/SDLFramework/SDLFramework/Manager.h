#pragma once
#include "IGameObject.h"
#include <SDL_render.h>
#include "Tile.h"
#include "Map.h"
#include "Globals.h"
#include "Artist.h"
#include "ManagerState.h"

enum class MANAGER_STATE_CHANGE { NO_STATE_CHANGE = 0, START_WANDERING = 1, GO_TO_ARTIST = 2 };
class ManagerState;

class Manager : public IGameObject
{
public:
	Tile* currentTile;
	Map* map;
	SDL_Texture *texture;
	std::vector<Tile*> path;
	std::vector<Artist*> artists;
	Artist* artistToVisit;
	ManagerState* state;
	Color color = Color(0, 255, 255, 255);

	int wait = 0;
	uint32_t msTimeBetweenActions = 1000; //Means the manager will execute an action every 1000 ms
	uint32_t msTimeOfLastAction = 0;

	Manager(Map* mapIn);
	void setColor(Color colorIn) { color = colorIn; }
	void addArtist(Artist* artist) { artists.push_back(artist); }
	void move();
	void changeState(ManagerState* stateIn) { state = stateIn; }
	~Manager();
	void Update(float deltaTime);

	MANAGER_STATE_CHANGE stateChange = MANAGER_STATE_CHANGE::NO_STATE_CHANGE;

};