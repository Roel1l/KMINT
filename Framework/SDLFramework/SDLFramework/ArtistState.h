#pragma once
#include "Artist.h"
#include "Globals.h"


class Artist;

class ArtistState
{
public:
	ArtistState() {};
	ArtistState(Artist* artistIn) { artist = artistIn; }
	~ArtistState();

	virtual void Update(float deltaTime) {};
	virtual void move() {};
	void checkState();

	Artist* artist;
};

