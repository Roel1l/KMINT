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
	virtual bool doesArtistNeedMoney() { return false; };
	void checkState();

	Artist* artist;

};

