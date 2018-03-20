#pragma once
#include "IGameObject.h"
#include "vector.h"
#include <random>
#include "Globals.h"
#include "Map.h"
#include "Tile.h"

class Fan : public IGameObject
{
public:
	Fan(int fanId, std::vector<Fan*>* fansIn, Map* mapIn);
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
	Map* map;

	//Behaviour
	bool STAY_NEAR_OTHERS = true;
	double STICK_RADIUS = 100;
	double STICK_INTENSITY = 0.01;

	bool AVOID_COLLISION = true;
	double COLLISION_RADIUS = 30;
	double COLLISION_INTENSITY = 1.5;

	bool MIMIC_DIRECTION = true;
	double MIMIC_RADIUS = 100;
	double MIMIC_INTENSITY = 0.1;

	bool RANDOM_STEERING = true;
	bool STEER_INTENSITY = 0.05;

	double SPEED = 2;


private:
	SDL_Texture *texture;
	std::vector<Fan*> getNearbyFans(double range);

};

