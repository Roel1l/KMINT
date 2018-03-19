#include "Bird.h"
#include <SDL_render.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "FlockingGlobals.h"
#define _USE_MATH_DEFINES
#include <math.h>



Bird::Bird(int birdId, std::vector<Bird*>* birdsIn)
{
	if (RANDOM_SPAWN) {
		x = generateRandom(0, SCREEN_WIDTH);
		y = generateRandom(0, SCREEN_HEIGTH);
	}
	else { x = SCREEN_WIDTH /2; y = SCREEN_HEIGTH /2; }

	birds = birdsIn;
	id = birdId;

	init();
	
}

Bird::Bird(int birdId, std::vector<Bird*>* birdsIn, int xIn, int yIn)
{
	x = xIn;
	y = yIn;

	birds = birdsIn;
	id = birdId;

	init();
}

Bird::~Bird()
{
	SDL_DestroyTexture(texture);
}


void Bird::init() {
	texture = mApplication->LoadTexture("square.png");
	this->SetTexture(texture);
	this->SetSize(10, 10);

	int a = generateRandom(-1000, 1000);
	int b = generateRandom(-1000, 1000);
	direction.setRichting(a, b);
}


void Bird::Update(float deltaTime) {

	double overstaande = direction.y;
	double lange = direction.getLength();

	angle = asin(overstaande / lange) * 180 / M_PI;
	angle += 90;

	double currVectorLength = direction.getLength();
	
	if (currVectorLength > SPEED) {
		direction.x = direction.x / currVectorLength * SPEED;
		direction.y = direction.y / currVectorLength * SPEED;
	}

	x = x + direction.x;
	y = y + direction.y;

	if (x > SCREEN_WIDTH) x = x - SCREEN_WIDTH;
	if (x < 0) x = x + SCREEN_WIDTH;
	if (y > SCREEN_HEIGTH) y = y - SCREEN_HEIGTH;
	if (y < 0) y = y + SCREEN_HEIGTH;

	Vector one = avoidCollision(getNearbyBirds(COLLISION_RADIUS));
	Vector two = mimicDirection(getNearbyBirds(MIMIC_RADIUS));
	Vector three = stayNearOthers(getNearbyBirds(STICK_RADIUS));
	Vector four = Steer();

	if (AVOID_COLLISION) { if(one.x != 0 || one.y != 0) direction.x += one.x; direction.y += one.y; }
	if (MIMIC_DIRECTION) { if (two.x != 0 || two.y != 0) direction.x += two.x; direction.y += two.y; }
	if (STAY_NEAR_OTHERS) { if (three.x != 0 || three.y != 0) direction.x += three.x; direction.y += three.y; }
	if (RANDOM_STEERING) { direction.x += four.x, direction.y += four.y; }

	SetOffset(x-5, y-5, angle);
}

Vector Bird::Steer()
{
	int power = 5;
	Vector returnVector;

	int squareX1 = direction.x *10 - power;
	int squareX2 = direction.x *10 + power;
	int squareY1 = direction.y *10 - power;
	int squareY2 = direction.y *10 + power;

	returnVector.x = generateRandom(squareX1, squareX2);
	returnVector.y = generateRandom(squareY1, squareY2);

	double length = returnVector.getLength();
	if (length > STEER_INTENSITY) {
		returnVector.x = returnVector.x / length * STEER_INTENSITY;
		returnVector.y = returnVector.y / length * STEER_INTENSITY;
	}

	return returnVector;
}

Vector Bird::avoidCollision(std::vector<Bird*> nearbyBirds) {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	for each (Bird* otherBird in nearbyBirds)
	{
		if (otherBird->id != id) {
			Vector temp;
			temp.x = 0;
			temp.y = 0;
			temp.x += x - otherBird->x;
			temp.y += y - otherBird->y;
			
			double length = temp.getLength();
			if (length > COLLISION_INTENSITY) {
				temp.x = temp.x / length * COLLISION_INTENSITY;
				temp.y = temp.y / length * COLLISION_INTENSITY;
			}

			returnVector.x += temp.x;
			returnVector.y += temp.y;
		}
	}
	
	return returnVector;

}

Vector Bird::mimicDirection(std::vector<Bird*> nearbyBirds) {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	for each (Bird* otherBird in nearbyBirds)
	{
		if (otherBird->id != id) {
			Vector temp;
			temp.x = 0;
			temp.y = 0;

			temp.x += otherBird->direction.x;
			temp.y += otherBird->direction.y;

			double length = temp.getLength();
			if (length > MIMIC_INTENSITY) {
				temp.x = temp.x / length * MIMIC_INTENSITY;
				temp.y = temp.y / length * MIMIC_INTENSITY;
			}

			returnVector.x += temp.x;
			returnVector.y += temp.y;
		}
	}

	return returnVector;
}

Vector Bird::stayNearOthers(std::vector<Bird*> nearbyBirds) {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;
	
	for each (Bird* otherBird in nearbyBirds)
	{
		if (otherBird->id != id) {
			Vector temp;
			temp.x = 0;
			temp.y = 0;
			temp.x += otherBird->x - x;
			temp.y += otherBird->y - y;

			double length = temp.getLength();
			if (length > STICK_INTENSITY) {
				temp.x = temp.x / length * STICK_INTENSITY;
				temp.y = temp.y / length * STICK_INTENSITY;
			}

			returnVector.x += temp.x;
			returnVector.y += temp.y;
		}
	}

	return returnVector;
}

Vector Bird::getOppositeVector(Vector v) {
	v.x = v.x - (v.x * 2);
	v.y = v.y - (v.y * 2);
	return v;
}

std::vector<Bird*> Bird::getNearbyBirds(double range)
{
	std::vector<Bird*> nearbyBirds;
	std::vector<Bird*>& birdsRef = *birds;
	for (int i = 0; i < birdsRef.size(); i++) {
		if (birdsRef[i]->x < x + range && birdsRef[i]->x > x - range && birdsRef[i]->y < y + range && birdsRef[i]->y > y - range) {
			nearbyBirds.push_back(birdsRef[i]);
		}
	}

	return nearbyBirds;
}


