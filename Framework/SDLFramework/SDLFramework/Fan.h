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

	uint32_t fitness = 0;

private:

	Vector getSteeringVector();
	Vector getSeparationVector(std::vector<Fan*> nearbyFans);
	Vector getAlignmentVector(std::vector<Fan*> nearbyFans);
	Vector getCohesionVector(std::vector<Fan*> nearbyFans);
	Vector getAttractedToArtistsVector();
	void move();

	Vector getOppositeVector(Vector v);
	Vector direction;

	int getPointsForBeingNearArtists();
	bool checkIfDead();

	SDL_Texture *texture;
	std::vector<Fan*> getNearbyFans(double range);


	double SPEED = 1;

};

