#include "ArtistWanderState.h"


void ArtistWanderState::Update(float deltaTime)
{
}

void ArtistWanderState::move()
{
	if (artist->path.size() <= 0) {
		int random = generateRandom(0, artist->map->walkableTileIndexes.size() - 1);
		Tile* target = artist->map->getTile(std::get<0>(artist->map->walkableTileIndexes[random]), std::get<1>(artist->map->walkableTileIndexes[random]));

		artist->path = artist->map->findPath(artist->currentTile, target);
	}

	artist->money = artist->money <= 0 ? 0 : artist->money - 20;
	artist->currentTile = artist->path[0];
	artist->path.erase(artist->path.begin());
	artist->wait = artist->currentTile->weight();
}

ArtistWanderState::~ArtistWanderState()
{
}
