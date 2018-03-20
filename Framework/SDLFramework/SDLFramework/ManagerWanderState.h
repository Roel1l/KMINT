#pragma once
#include "ManagerState.h"

class ManagerWanderState : public ManagerState
{
public:
	ManagerWanderState(Manager* managerIn) { manager = managerIn; }

	void Update(float deltaTime);
	void move();

	~ManagerWanderState();
};


