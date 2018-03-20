#pragma once
#include "ArtistState.h"

class ArtistShopState : public ArtistState
{
public:
	ArtistShopState(Artist* artistIn);

	void Update(float deltaTime);
	void move();
	bool doesArtistNeedMoney() { return false; }

	~ArtistShopState();
};
