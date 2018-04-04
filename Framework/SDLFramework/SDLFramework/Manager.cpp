#include "Manager.h"
#include "ManagerWanderState.h"

void Manager::Update(float deltaTime)
{
	uint32_t msTimeCurrent = mApplication->GetTimeSinceStartedMS();

	if (msTimeCurrent - msTimeOfLastAction >= (double)msTimeBetweenActions * GLOBAL_SPEED) {
		msTimeOfLastAction = msTimeCurrent;
		state->checkState();
		state->Update(deltaTime);
		wait = wait <= 0 ? 0 : wait - 1;
		if (wait < 1) move();
	}

	mApplication->SetColor(color);
	mApplication->DrawRect(currentTile->absoluteX + 1, currentTile->absoluteY + 1, 18, 18, true);
}

Manager::Manager(Map * mapIn)
{
	map = mapIn;
}

void Manager::spawn() {
	wait = 0;
	delete state;
	state = new ManagerWanderState(this);
	int random = generateRandom(0, map->walkableTileIndexes.size() - 1);
	currentTile = map->getTile(std::get<0>(map->walkableTileIndexes[random]), std::get<1>(map->walkableTileIndexes[random]));
}

void Manager::move()
{
	state->move();
}

Manager::~Manager()
{
	delete state;
	SDL_DestroyTexture(texture);
}