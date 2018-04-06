#pragma once
#include "IGameObject.h"
#include "vector.h"
#include <random>
#include "Globals.h"
#include "Map.h"
#include "Tile.h"
#include "Artist.h"
#include <map>

class Fan : public IGameObject
{
public:
	Fan(int fanId, std::vector<Fan*>* fansIn, Map* mapIn, std::vector<Artist*> artistsIn);
	~Fan();
	void Update(float deltaTime);
	void initRandomStartingValues();
	void spawn();

	int id;
	double x;
	double y;
	bool dead = false;

	Map* map;

	std::vector<Artist*> artists;
	std::vector<Fan*>* fans;

	std::map<std::string, double> chromosome;

	std::string mutation = "";

	uint32_t fitness = 1;

private:

	Vector getSteeringVector();
	Vector getCollisionVector(std::vector<Fan*> nearbyFans);
	Vector getSeparationVector(std::vector<Fan*> nearbyFans);
	Vector getAlignmentVector(std::vector<Fan*> nearbyFans);
	Vector getCohesionVector(std::vector<Fan*> nearbyFans);
	Vector getAttractedToArtistsVector(std::vector<Artist*> nearbyArtists);
	void move();

	Vector getOppositeVector(Vector v);
	Vector direction;

	int getPointsForBeingNearArtists();
	bool checkIfDead();

	std::vector<Fan*> getNearbyFans(double range);
	std::vector<Artist*> getNearbyArtists(double range);

	SDL_Texture *texture;

	double SPEED = 1;

};

