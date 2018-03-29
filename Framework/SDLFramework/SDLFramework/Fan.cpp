#include "Fan.h"
#include <SDL_render.h>
#include <chrono>
#include <thread>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

Fan::Fan(int fanId, std::vector<Fan*>* fansIn, Map* mapIn)
{
	fans = fansIn;
	id = fanId;
	map = mapIn;
}

Fan::~Fan()
{
	SDL_DestroyTexture(texture);
}

void Fan::Update(float deltaTime) {

	if (!dead) {
		dead = checkIfDead();
		nearArtistsPoints += getPointsForBeingNearArtists();

		double currVectorLength = direction.getLength();
		if (currVectorLength > SPEED) {
			direction.x = direction.x / currVectorLength * SPEED;
			direction.y = direction.y / currVectorLength * SPEED;
		}

		move();

		Vector one = avoidCollision(getNearbyFans(COLLISION_RADIUS));
		Vector two = mimicDirection(getNearbyFans(MIMIC_RADIUS));
		Vector three = stayNearOthers(getNearbyFans(STICK_RADIUS));
		Vector four = Steer();


		if (AVOID_COLLISION) { if (one.x != 0 || one.y != 0) direction.x += one.x; direction.y += one.y; }
		if (MIMIC_DIRECTION) { if (two.x != 0 || two.y != 0) direction.x += two.x; direction.y += two.y; }
		if (STAY_NEAR_OTHERS) { if (three.x != 0 || three.y != 0) direction.x += three.x; direction.y += three.y; }
		if (RANDOM_STEERING) { direction.x += four.x, direction.y += four.y; }

		//Artists
		if (STAY_NEAR_ARTISTS) {
			Vector axel = goToAxel();
			Vector johnnie = goToJohnnie();
			Vector frans = goToFrans();
			Vector andre = goToAndre();
			if (axel.x != 0 || axel.y != 0) direction.x += axel.x; direction.y += axel.y;
			if (johnnie.x != 0 || johnnie.y != 0) direction.x += johnnie.x; direction.y += johnnie.y;
			if (frans.x != 0 || frans.y != 0) direction.x += frans.x; direction.y += frans.y;
			if (andre.x != 0 || andre.y != 0) andre.x += andre.x; direction.y += andre.y;
		}

		mApplication->SetColor(Color(0, 0, 0, 255));
		mApplication->DrawRect(x, y, 5, 5, true);
	}
}

Vector Fan::Steer()
{
	int power = 5;
	Vector returnVector;

	int squareX1 = direction.x * 10 - power;
	int squareX2 = direction.x * 10 + power;
	int squareY1 = direction.y * 10 - power;
	int squareY2 = direction.y * 10 + power;

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
			temp.x += otherFan->x - x + 2;
			temp.y += otherFan->y - y + 2;

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

Vector Fan::goToAxel() {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	Vector temp;
	temp.x = 0;
	temp.y = 0;
	temp.x += axel->currentTile->absoluteX + 10 - x;
	temp.y += axel->currentTile->absoluteY + 10 - y;

	double length = temp.getLength();
	if (length > ATTRACTED_TO_AXEL) {
		temp.x = temp.x / length * ATTRACTED_TO_AXEL;
		temp.y = temp.y / length * ATTRACTED_TO_AXEL;
	}

	returnVector.x += temp.x;
	returnVector.y += temp.y;

	return returnVector;
}

Vector Fan::goToJohnnie() {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	Vector temp;
	temp.x = 0;
	temp.y = 0;
	temp.x += johnnie->currentTile->absoluteX + 10 - x;
	temp.y += johnnie->currentTile->absoluteY + 10 - y;

	double length = temp.getLength();
	if (length > ATTRACTED_TO_JOHNNIE) {
		temp.x = temp.x / length * ATTRACTED_TO_JOHNNIE;
		temp.y = temp.y / length * ATTRACTED_TO_JOHNNIE;
	}

	returnVector.x += temp.x;
	returnVector.y += temp.y;

	return returnVector;
}

Vector Fan::goToAndre() {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	Vector temp;
	temp.x = 0;
	temp.y = 0;
	temp.x += andre->currentTile->absoluteX + 10 - x;
	temp.y += andre->currentTile->absoluteY + 10 - y;

	double length = temp.getLength();
	if (length > ATTRACTED_TO_ANDRE) {
		temp.x = temp.x / length * ATTRACTED_TO_ANDRE;
		temp.y = temp.y / length * ATTRACTED_TO_ANDRE;
	}

	returnVector.x += temp.x;
	returnVector.y += temp.y;

	return returnVector;
}

Vector Fan::goToFrans() {
	Vector returnVector;
	returnVector.x = 0;
	returnVector.y = 0;

	Vector temp;
	temp.x = 0;
	temp.y = 0;
	temp.x += frans->currentTile->absoluteX + 10 - x;
	temp.y += frans->currentTile->absoluteY + 10 - y;

	double length = temp.getLength();
	if (length > ATTRACTED_TO_FRANS) {
		temp.x = temp.x / length * ATTRACTED_TO_FRANS;
		temp.y = temp.y / length * ATTRACTED_TO_FRANS;
	}

	returnVector.x += temp.x;
	returnVector.y += temp.y;

	return returnVector;
}

void Fan::move() {
	int correctionX = x + direction.x > x ? 4 : 0;
	int correctionY = y + direction.y > y ? 4 : 0;

	Tile * tileX = map->getTileByCoordinates(x + direction.x + correctionX, y + direction.y);
	Tile * tileY = map->getTileByCoordinates(x, y + direction.y + correctionY);

	bool canMoveX = tileX->type != '1' && tileX->type != '2' && tileX->type != '3' ? false : true;

	bool canMoveY = tileY->type != '1' && tileY->type != '2' && tileY->type != '3' ? false : true;

	if (canMoveX) x = x + direction.x;
	if (canMoveY) y = y + direction.y;
}

int Fan::getPointsForBeingNearArtists() {

	int returnValue = 0;

	if (x >= axel->currentTile->absoluteX - NEAR_ARTIST_RADIUS &&
		x <= axel->currentTile->absoluteX + axel->width + NEAR_ARTIST_RADIUS &&
		y >= axel->currentTile->absoluteY - NEAR_ARTIST_RADIUS &&
		y <= axel->currentTile->absoluteY + axel->heigth + NEAR_ARTIST_RADIUS
		) {
		returnValue++;
	}

	if (x >= johnnie->currentTile->absoluteX - NEAR_ARTIST_RADIUS &&
		x <= johnnie->currentTile->absoluteX + johnnie->width + NEAR_ARTIST_RADIUS &&
		y >= johnnie->currentTile->absoluteY - NEAR_ARTIST_RADIUS &&
		y <= johnnie->currentTile->absoluteY + johnnie->heigth + NEAR_ARTIST_RADIUS
		) {
		returnValue++;
	}

	if (x >= andre->currentTile->absoluteX - NEAR_ARTIST_RADIUS &&
		x <= andre->currentTile->absoluteX + andre->width + NEAR_ARTIST_RADIUS &&
		y >= andre->currentTile->absoluteY - NEAR_ARTIST_RADIUS &&
		y <= andre->currentTile->absoluteY + andre->heigth + NEAR_ARTIST_RADIUS
		) {
		returnValue++;
	}

	if (x >= frans->currentTile->absoluteX - NEAR_ARTIST_RADIUS &&
		x <= frans->currentTile->absoluteX + frans->width + NEAR_ARTIST_RADIUS &&
		y >= frans->currentTile->absoluteY - NEAR_ARTIST_RADIUS &&
		y <= frans->currentTile->absoluteY + frans->heigth + NEAR_ARTIST_RADIUS
		) {
		returnValue++;
	}

	return returnValue;
}

bool Fan::checkIfDead() {
	return
		x >= johnnie->currentTile->absoluteX - 15 &&
		x <= johnnie->currentTile->absoluteX + johnnie->width + 15 &&
		y >= johnnie->currentTile->absoluteY - 15 &&
		y <= johnnie->currentTile->absoluteY + johnnie->heigth + 15
		?
		true : false;
}

void Fan::initRandomStartingValues() {

	ATTRACTED_TO_AXEL = (double)generateRandom(-100, 100) / 100;
	ATTRACTED_TO_FRANS = (double)generateRandom(-100, 100) / 100;
	ATTRACTED_TO_JOHNNIE = (double)generateRandom(-100, 100) / 100;
	ATTRACTED_TO_ANDRE = (double)generateRandom(-100, 100) / 100;
	STICK_INTENSITY = (double)generateRandom(0, 100) / 100;
	COLLISION_INTENSITY = (double)generateRandom(0, 100) / 100;
	MIMIC_INTENSITY = (double)generateRandom(0, 100) / 100;
}

void Fan::spawn() {
	int random = generateRandom(0, map->walkableTileIndexes.size() - 1);
	Tile* spawnTile = map->getTile(std::get<0>(map->walkableTileIndexes[random]), std::get<1>(map->walkableTileIndexes[random]));

	x = spawnTile->absoluteX + 7;
	y = spawnTile->absoluteY + 8;

	int a = generateRandom(-1000, 1000);
	int b = generateRandom(-1000, 1000);
	direction.setRichting(a, b);
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


