#include "Fan.h"
#include <SDL_render.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "FlockingGlobals.h"
#define _USE_MATH_DEFINES
#include <math.h>

Fan::Fan(int fanId, std::vector<Fan*>* fansIn)
{
	if (RANDOM_SPAWN) {
		x = generateRandom(0, SCREEN_WIDTH);
		y = generateRandom(0, SCREEN_HEIGTH);
	}
	else { x = SCREEN_WIDTH /2; y = SCREEN_HEIGTH /2; }

	fans = fansIn;
	id = fanId;

	init();
	
}

Fan::Fan(int fanId, std::vector<Fan*>* fansIn, int xIn, int yIn)
{
	x = xIn;
	y = yIn;

	fans = fansIn;
	id = fanId;

	init();
}

Fan::~Fan()
{
	SDL_DestroyTexture(texture);
}


void Fan::init() {

	int a = generateRandom(-1000, 1000);
	int b = generateRandom(-1000, 1000);
	direction.setRichting(a, b);
}


void Fan::Update(float deltaTime) {

	double overstaande = direction.y;
	double lange = direction.getLength();

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

	Vector one = avoidCollision(getNearbyFans(COLLISION_RADIUS));
	Vector two = mimicDirection(getNearbyFans(MIMIC_RADIUS));
	Vector three = stayNearOthers(getNearbyFans(STICK_RADIUS));
	Vector four = Steer();

	if (AVOID_COLLISION) { if(one.x != 0 || one.y != 0) direction.x += one.x; direction.y += one.y; }
	if (MIMIC_DIRECTION) { if (two.x != 0 || two.y != 0) direction.x += two.x; direction.y += two.y; }
	if (STAY_NEAR_OTHERS) { if (three.x != 0 || three.y != 0) direction.x += three.x; direction.y += three.y; }
	if (RANDOM_STEERING) { direction.x += four.x, direction.y += four.y; }

	mApplication->SetColor(Color(0,0,0,255));
	mApplication->DrawRect(x, y, 5, 5, true);
}

Vector Fan::Steer()
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

Vector Fan::avoidCollision(std::vector<Fan*> nearbyFans) {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	for each (Fan* otherFan in nearbyFans)
	{
		if (otherFan->id != id) {
			Vector temp;
			temp.x = 0;
			temp.y = 0;
			temp.x += x - otherFan->x;
			temp.y += y - otherFan->y;
			
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

Vector Fan::mimicDirection(std::vector<Fan*> nearbyFans) {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	for each (Fan* otherFan in nearbyFans)
	{
		if (otherFan->id != id) {
			Vector temp;
			temp.x = 0;
			temp.y = 0;

			temp.x += otherFan->direction.x;
			temp.y += otherFan->direction.y;

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

Vector Fan::stayNearOthers(std::vector<Fan*> nearbyFans) {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;
	
	for each (Fan* otherFan in nearbyFans)
	{
		if (otherFan->id != id) {
			Vector temp;
			temp.x = 0;
			temp.y = 0;
			temp.x += otherFan->x - x;
			temp.y += otherFan->y - y;

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

Vector Fan::getOppositeVector(Vector v) {
	v.x = v.x - (v.x * 2);
	v.y = v.y - (v.y * 2);
	return v;
}

std::vector<Fan*> Fan::getNearbyFans(double range)
{
	std::vector<Fan*> nearbyFans;
	std::vector<Fan*>& fansRef = *fans;
	for (int i = 0; i < fansRef.size(); i++) {
		if (fansRef[i]->x < x + range && fansRef[i]->x > x - range && fansRef[i]->y < y + range && fansRef[i]->y > y - range) {
			nearbyFans.push_back(fansRef[i]);
		}
	}

	return nearbyFans;
}


