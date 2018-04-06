#pragma once
#include "IGameObject.h"
#include <SDL_render.h>
#include "Tile.h"
#include "Map.h"
#include "Globals.h"
#include "ArtistState.h"

enum class ARTIST_STATE_CHANGE { NO_STATE_CHANGE, START_WANDERING, MANAGER_IS_COMING, GO_TO_SHOP };
class ArtistState;

class Artist : public IGameObject
{
public:

	std::string name = "NO NAME";

	Tile* currentTile;
	Map* map;
	SDL_Texture *texture;
	std::vector<Tile*> path;
	ArtistState* state;
	Color color = Color(0, 0, 102, 255);
	bool hostile = false;

	int width = 16;
	int heigth = 16;

	int money = 1000;
	int wait = 0;
	uint32_t msTimeBetweenActions = 500; //Means the artist will execute an action every 500 ms
	uint32_t msTimeOfLastAction = 0;

	Artist(Map* mapIn);
	void spawn();
	void setColor(Color colorIn) { color = colorIn; }
	void move();
	bool doesArtistNeedMoney();
	void changeState(ArtistState* stateIn) { state = stateIn; }
	~Artist();
	void Update(float deltaTime);

	void Draw();

	ARTIST_STATE_CHANGE stateChange = ARTIST_STATE_CHANGE::NO_STATE_CHANGE;
};

