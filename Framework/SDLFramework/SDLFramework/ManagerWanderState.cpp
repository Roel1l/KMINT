#include "ManagerWanderState.h"

ManagerWanderState::~ManagerWanderState()
{
}

void ManagerWanderState::Update(float deltaTime)
{
}

void ManagerWanderState::move()
{
	// If there's no path to walk choose random path to walk
	if (manager->path.size() <= 0) {
		int random = generateRandom(0, manager->map->walkableTileIndexes.size() - 1);
		Tile* target = manager->map->getTile(std::get<0>(manager->map->walkableTileIndexes[random]), std::get<1>(manager->map->walkableTileIndexes[random]));

		manager->path = manager->map->findPath(manager->currentTile, target);
	}

	// Moving 1 step
	if (manager->path.size() > 0) {
		manager->currentTile = manager->path[0];
		manager->path.erase(manager->path.begin());
		manager->wait = manager->currentTile->weight();
	}

	//Check if an artist needs help
	for each(Artist* artist in manager->artists) {
		if (artist->doesArtistNeedMoney()) {
			artist->stateChange = ARTIST_STATE_CHANGE::MANAGER_IS_COMING;
			manager->stateChange = MANAGER_STATE_CHANGE::GO_TO_ARTIST;
			manager->artistToVisit = artist;
			manager->path.clear();
			break;
		}
	}
}
