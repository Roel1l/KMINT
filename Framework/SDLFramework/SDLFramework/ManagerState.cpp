#include "ManagerState.h"
#include "ManagerWanderState.h"
#include "ManagerVisitArtistState.h"

ManagerState::~ManagerState()
{
}

void ManagerState::checkState()
{
	switch (manager->stateChange) {
	case MANAGER_STATE_CHANGE::NO_STATE_CHANGE:
		break;
	case MANAGER_STATE_CHANGE::START_WANDERING:
		manager->stateChange = MANAGER_STATE_CHANGE::NO_STATE_CHANGE;
		manager->changeState(new ManagerWanderState(manager));
		break;
	case MANAGER_STATE_CHANGE::GO_TO_ARTIST:
		manager->stateChange = MANAGER_STATE_CHANGE::NO_STATE_CHANGE;
		manager->changeState(new ManagerVisitArtistState(manager));
		break;
	default:
		break;
	}
}