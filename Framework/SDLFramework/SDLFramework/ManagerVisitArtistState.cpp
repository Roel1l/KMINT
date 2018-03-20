#include "ManagerVisitArtistState.h"


void ManagerVisitArtistState::Update(float deltaTime)
{
}

void ManagerVisitArtistState::move()
{
	// If there's no path set path to walk to artist that needs help
	if (manager->path.size() <= 0) {
		Tile* target = manager->map->getTile(manager->artistToVisit->currentTile->gridX(), manager->artistToVisit->currentTile->gridY());

		manager->path = manager->map->findPath(manager->currentTile, target);
	}

	// Moving 1 step
	manager->currentTile = manager->path[0];
	//manager->currentTile->partOfPath = false;
	manager->path.erase(manager->path.begin());
	manager->wait = manager->currentTile->weight();

	if (manager->currentTile == manager->artistToVisit->currentTile) {
			manager->artistToVisit->stateChange = ARTIST_STATE_CHANGE::GO_TO_SHOP;
			manager->stateChange = MANAGER_STATE_CHANGE::START_WANDERING;
	}
	

	//if (SHOW_PATH) for each (Tile* t in manager->path) t->partOfPath = true;
}

ManagerVisitArtistState::~ManagerVisitArtistState()
{
}
