#pragma once
#include "IGameObject.h"
#include "vector.h"
#include <random>
#include "Globals.h"

class Bird : public IGameObject
{
public:
	Bird(int birdId, std::vector<Bird*>* b);
	Bird(int birdId, std::vector<Bird*>* birdsIn, int xIn, int yIn);
	void init();
	~Bird();
	void Update(float deltaTime);
	Vector Steer();
	Vector avoidCollision(std::vector<Bird*> nearbyBirds);
	Vector mimicDirection(std::vector<Bird*> nearbyBirds);
	Vector stayNearOthers(std::vector<Bird*> nearbyBirds);
	Vector getOppositeVector(Vector v);
	Vector direction;
	double x;
	double y;
	int angle;
	int id;
	std::vector<Bird*>* birds;
private:
	int screenWidth = 1280;
	int screenHeigth = 720;
	SDL_Texture *texture;
	std::vector<Bird*> getNearbyBirds(double range);

};

