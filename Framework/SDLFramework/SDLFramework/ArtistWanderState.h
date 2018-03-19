#pragma once
#include "ArtistState.h"

class ArtistWanderState : public ArtistState
{
public:
	ArtistWanderState(Artist* artistIn) { artist = artistIn; }

	void Update(float deltaTime);
	void move();

	~ArtistWanderState();
};

