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
	Vector getSteeringVector();
	Vector getSeparationVector(std::vector<Fan*> nearbyFans);
	Vector getAlignmentVector(std::vector<Fan*> nearbyFans);
	Vector getCohesionVector(std::vector<Fan*> nearbyFans);
	Vector getAttractedToArtistsVector();
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

	std::vector<Artist*> artists;
	std::map<std::string, double> chromosome;

	//Behaviour
	double SPEED = 1;


	uint32_t nearArtistsPoints = 0;

private:
	SDL_Texture *texture;
	std::vector<Fan*> getNearbyFans(double range);

};

