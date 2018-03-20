#pragma once
#include "Manager.h"

class Manager;

class ManagerState
{
public:
	ManagerState() {};
	ManagerState(Manager* managerIn) { manager = managerIn; }
	~ManagerState();

	virtual void Update(float deltaTime) {};
	virtual void move() {};
	void checkState();

	Manager* manager;
};

