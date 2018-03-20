#pragma once
#include "ManagerState.h"

class ManagerVisitArtistState : public ManagerState
{
public:
	ManagerVisitArtistState(Manager* managerIn);

	void Update(float deltaTime);
	void move();

	~ManagerVisitArtistState();
};

