#include "Artist.h"
#include "ArtistWanderState.h"

void Artist::Update(float deltaTime)
{
	uint32_t msTimeCurrent = mApplication->GetTimeSinceStartedMS();

	if (msTimeCurrent - msTimeOfLastAction >= msTimeBetweenActions * GLOBAL_SPEED) {
		msTimeOfLastAction = msTimeCurrent;
		state->checkState();
		state->Update(deltaTime);
		wait = wait <= 0 ? 0 : wait - 1;
		if(wait < 1) move();
	}

	mApplication->SetColor(color);
	mApplication->DrawCircle(currentTile->absoluteX + 10, currentTile->absoluteY + 10, 10, true);
}


Artist::Artist(Map * mapIn)
{
	map = mapIn; 
	state = new ArtistWanderState(this);
	currentTile = map->getTile(1, 1);
}

void Artist::move() {
	state->move();
}

Artist::~Artist()
{
	delete state;
	SDL_DestroyTexture(texture);
}
