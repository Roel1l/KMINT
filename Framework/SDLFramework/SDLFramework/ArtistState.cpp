#include "ArtistState.h"
#include "ArtistWaitState.h"
#include "ArtistWanderState.h"
#include "ArtistShopState.h"

ArtistState::~ArtistState()
{
}

void ArtistState::checkState()
{
	switch (artist->stateChange) {
	case ARTIST_STATE_CHANGE::NO_STATE_CHANGE:
		break;
	case ARTIST_STATE_CHANGE::START_WANDERING:
		artist->stateChange = ARTIST_STATE_CHANGE::NO_STATE_CHANGE;
		artist->changeState(new ArtistWanderState(artist));	
		delete this;
		break;
	case ARTIST_STATE_CHANGE::MANAGER_IS_COMING:
		artist->stateChange = ARTIST_STATE_CHANGE::NO_STATE_CHANGE;
		artist->changeState(new ArtistWaitState(artist));
		delete this;
		break;
	case ARTIST_STATE_CHANGE::GO_TO_SHOP:
		artist->stateChange = ARTIST_STATE_CHANGE::NO_STATE_CHANGE;
		artist->changeState(new ArtistShopState(artist));
		delete this;
		break;
	default:
		break;
	}
}
