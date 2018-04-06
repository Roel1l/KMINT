#include "Artist.h"
#include "ArtistWanderState.h"

void Artist::Update(float deltaTime)
{
		state->checkState();
		state->Update(deltaTime);
		wait = wait <= 0 ? 0 : wait - 1;
		if(wait < 1) move();
}

void Artist::Draw() {
	mApplication->SetColor(color);
	//mApplication->DrawCircle(currentTile->absoluteX + 10, currentTile->absoluteY + 10, 10, true);
	mApplication->DrawRect(currentTile->absoluteX + 2, currentTile->absoluteY + 2, width, heigth, true);
}

Artist::Artist(Map * mapIn)
{
	map = mapIn; 
}

void Artist::spawn() {
	money = 1000;
	wait = 0;
	delete state;
	state = new ArtistWanderState(this);
	int random = generateRandom(0, map->walkableTileIndexes.size() - 1);
	currentTile = map->getTile(std::get<0>(map->walkableTileIndexes[random]), std::get<1>(map->walkableTileIndexes[random]));
}

void Artist::move() {
	state->move();
}

bool Artist::doesArtistNeedMoney()
{
	return state->doesArtistNeedMoney();
}

Artist::~Artist()
{
	delete state;
	SDL_DestroyTexture(texture);
}
