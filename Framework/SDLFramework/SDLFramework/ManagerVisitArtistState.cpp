#include "ManagerVisitArtistState.h"


ManagerVisitArtistState::ManagerVisitArtistState(Manager * managerIn)
{
	manager = managerIn;
	name = "ManagerVisitArtistState";

	// Set Path to Artist
	Tile* target = manager->map->getTile(manager->artistToVisit->currentTile->gridX(), manager->artistToVisit->currentTile->gridY());

	manager->path = manager->map->findPath(manager->currentTile, target);
}

void ManagerVisitArtistState::Update(float deltaTime)
{
}

void ManagerVisitArtistState::move()
{
	// Moving 1 step
	if (manager->path.size() > 0) {
		manager->currentTile = manager->path[0];
		manager->path.erase(manager->path.begin());
		manager->wait = manager->currentTile->weight();
	}

	// Manager Arrived at Artist that he needed to help
	if (manager->path.size() <= 0) {
			manager->artistToVisit->stateChange = ARTIST_STATE_CHANGE::GO_TO_SHOP;
			manager->stateChange = MANAGER_STATE_CHANGE::START_WANDERING;
	}
	
}

ManagerVisitArtistState::~ManagerVisitArtistState()
{
}
