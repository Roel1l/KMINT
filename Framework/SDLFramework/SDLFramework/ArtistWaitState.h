#pragma once
#include "ArtistState.h"

class ArtistWaitState : public ArtistState
{
public:
	ArtistWaitState(Artist* artistIn);

	void Update(float deltaTime);
	void move();
	bool doesArtistNeedMoney() { return false; }

	~ArtistWaitState();
};
