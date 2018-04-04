#pragma once
#include "ManagerState.h"

class ManagerWanderState : public ManagerState
{
public:
	ManagerWanderState(Manager* managerIn) { manager = managerIn; name = "ManagerWanderState"; }

	void Update(float deltaTime);
	void move();

	~ManagerWanderState();
};


