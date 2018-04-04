#include "ArtistShopState.h"

ArtistShopState::ArtistShopState(Artist * artistIn)
{
	artist = artistIn;
	name = "ArtistShopState";

	//Set Path To random Shop
	int randomShop = generateRandom(0, artist->map->shopTileIndexes.size() - 1);
	Tile* target = artist->map->getTile(std::get<0>(artist->map->shopTileIndexes[randomShop]), std::get<1>(artist->map->shopTileIndexes[randomShop]));

	artist->path = artist->map->findPath(artist->currentTile, target);
}

void ArtistShopState::Update(float deltaTime)
{

}

void ArtistShopState::move()
{
	// Walk a step
	if (artist->path.size() > 0) {
		artist->money = artist->money <= 0 ? 0 : artist->money - 20;
		artist->currentTile = artist->path[0];
		artist->path.erase(artist->path.begin());
		artist->wait = artist->currentTile->weight();
	}

	//Found Store
	if (artist->path.size() <= 0) {
		artist->money += artist->currentTile->getPayOut();
		artist->stateChange = ARTIST_STATE_CHANGE::START_WANDERING;
	}
}

ArtistShopState::~ArtistShopState()
{
}
