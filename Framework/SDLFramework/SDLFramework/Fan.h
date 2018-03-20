#pragma once
#include "IGameObject.h"
#include "vector.h"
#include <random>
#include "Globals.h"

class Fan : public IGameObject
{
public:
	Fan(int fanId, std::vector<Fan*>* fansIn);
	Fan(int fanId, std::vector<Fan*>* fansIn, int xIn, int yIn);
	void init();
	~Fan();
	void Update(float deltaTime);
	Vector Steer();
	Vector avoidCollision(std::vector<Fan*> nearbyFans);
	Vector mimicDirection(std::vector<Fan*> nearbyFans);
	Vector stayNearOthers(std::vector<Fan*> nearbyFans);
	Vector getOppositeVector(Vector v);
	Vector direction;
	double x;
	double y;
	int id;
	std::vector<Fan*>* fans;
private:
	SDL_Texture *texture;
	std::vector<Fan*> getNearbyFans(double range);

};

