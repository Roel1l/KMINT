#pragma once
#include "ArtistState.h"

class ArtistWanderState : public ArtistState
{
public:
	ArtistWanderState(Artist* artistIn) { artist = artistIn; name = "ArtistWanderState";	}

	void Update(float deltaTime);
	void move();
	bool doesArtistNeedMoney() { return artist->money < 100; }

	~ArtistWanderState();
};

