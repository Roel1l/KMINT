#pragma once
#include "IGameObject.h"
#include "vector.h"
#include <random>
#include "Globals.h"
#include "Map.h"
#include "Tile.h"
#include "Artist.h"

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
	Vector goToAxel();
	Vector goToJohnnie();
	Vector goToAndre();
	Vector goToFrans();
	void move();
	int getPointsForBeingNearArtists();
	bool checkIfDead();
	void initRandomStartingValues();
	void spawn();
	Vector getOppositeVector(Vector v);
	Vector direction;
	double x;
	double y;
	int id;
	std::vector<Fan*>* fans;
	Map* map;

	bool dead = false;

	//Behaviour
	double SPEED = 1;

	const bool STAY_NEAR_OTHERS = true;
	const double STICK_RADIUS = 100;
	double STICK_INTENSITY = 0.01;

	const bool AVOID_COLLISION = true;
	const double COLLISION_RADIUS = 8;
	double COLLISION_INTENSITY = 1.0;

	const bool MIMIC_DIRECTION = true;
	double MIMIC_RADIUS = 100; 
	double MIMIC_INTENSITY = 0.1;

	const bool RANDOM_STEERING = true;
	bool STEER_INTENSITY = 0.05;

	const bool STAY_NEAR_ARTISTS = true;
	const double NEAR_ARTIST_RADIUS = 30;
	uint32_t nearArtistsPoints = 0;

	Artist* axel;
	double ATTRACTED_TO_AXEL = 1.0;

	Artist* johnnie;
	double ATTRACTED_TO_JOHNNIE = 1.0;

	Artist* frans;
	double ATTRACTED_TO_FRANS = 1.0;

	Artist* andre;
	double ATTRACTED_TO_ANDRE = 1.0;

private:
	SDL_Texture *texture;
	std::vector<Fan*> getNearbyFans(double range);

};

