#include "ArtistWaitState.h"

ArtistWaitState::ArtistWaitState(Artist * artistIn)
{
	artist = artistIn;
	name = "ArtistWaitState";

	artist->path.clear();
}

void ArtistWaitState::Update(float deltaTime)
{
}

void ArtistWaitState::move()
{
}

ArtistWaitState::~ArtistWaitState()
{
}
