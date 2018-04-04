#include "Fan.h"
#include <SDL_render.h>
#include <chrono>
#include <thread>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

Fan::Fan(int fanId, std::vector<Fan*>* fansIn, Map* mapIn, std::vector<Artist*> artistsIn)
{
	fans = fansIn;
	id = fanId;
	map = mapIn;
	artists = artistsIn;
}

Fan::~Fan()
{
	SDL_DestroyTexture(texture);
}

void Fan::Update(float deltaTime) {

	if (!dead) {
		dead = checkIfDead();
		fitness += getPointsForBeingNearArtists();

		double currVectorLength = direction.getLength();
		if (currVectorLength > SPEED) {
			direction.x = direction.x / currVectorLength * SPEED;
			direction.y = direction.y / currVectorLength * SPEED;
		}

		move();

		Vector separation = getSeparationVector(getNearbyFans(SEPARATION_RADIUS));
		Vector alignment = getAlignmentVector(getNearbyFans(MIMIC_RADIUS));
		Vector cohesion = getCohesionVector(getNearbyFans(COHESION_RADIUS));
		Vector artists = getAttractedToArtistsVector();
		Vector steer = getSteeringVector();

		if (SEPARATION) { direction.x += separation.x; direction.y += separation.y; }
		if (ALIGNMENT) { direction.x += alignment.x; direction.y += alignment.y; }
		if (COHESION) { direction.x += cohesion.x; direction.y += cohesion.y; }
		if (STAY_NEAR_ARTISTS) { direction.x += artists.x; direction.y += artists.y; }
		if (STEERING) { direction.x += steer.x, direction.y += steer.y; }

		mApplication->SetColor(Color(0, 0, 0, 255));
		mApplication->DrawRect(x, y, 5, 5, true);
	}
}

Vector Fan::getSteeringVector()
{
	int power = 5;
	Vector returnVector;

	int squareX1 = direction.x * 2 - power;
	int squareX2 = direction.x * 2 + power;
	int squareY1 = direction.y * 2 - power;
	int squareY2 = direction.y * 2 + power;

	returnVector.x = generateRandom(squareX1, squareX2);
	returnVector.y = generateRandom(squareY1, squareY2);

	double length = returnVector.getLength();
	if (length > STEER_INTENSITY) {
		returnVector.x = returnVector.x / length * STEER_INTENSITY;
		returnVector.y = returnVector.y / length * STEER_INTENSITY;
	}

	return returnVector;
}

Vector Fan::getSeparationVector(std::vector<Fan*> nearbyFans) {
	Vector returnVector;

	for each (Fan* otherFan in nearbyFans)
	{
		if (otherFan->id != id) {
			Vector temp;
			temp.x += x - otherFan->x;
			temp.y += y - otherFan->y;

			double length = temp.getLength();
			double separation = chromosome.at("separation");
			if (length > separation) {
				temp.x = temp.x / length * separation;
				temp.y = temp.y / length * separation;
			}

			returnVector.x += temp.x;
			returnVector.y += temp.y;
		}
	}

	return returnVector;

}

Vector Fan::getAlignmentVector(std::vector<Fan*> nearbyFans) {
	Vector returnVector;

	for each (Fan* otherFan in nearbyFans)
	{
		if (otherFan->id != id) {
			Vector temp;

			temp.x += otherFan->direction.x;
			temp.y += otherFan->direction.y;

			double length = temp.getLength();
			double alignment = chromosome.at("alignment");

			if (length > alignment) {
				temp.x = temp.x / length * alignment;
				temp.y = temp.y / length * alignment;
			}

			returnVector.x += temp.x;
			returnVector.y += temp.y;
		}
	}

	return returnVector;
}

Vector Fan::getCohesionVector(std::vector<Fan*> nearbyFans) {
	Vector returnVector;

	for each (Fan* otherFan in nearbyFans)
	{
		if (otherFan->id != id) {
			Vector temp;
			temp.x += otherFan->x - x + 2;
			temp.y += otherFan->y - y + 2;

			double length = temp.getLength();
			double cohesion = chromosome.at("cohesion");
			if (length > cohesion) {
				temp.x = temp.x / length * cohesion;
				temp.y = temp.y / length * cohesion;
			}

			returnVector.x += temp.x;
			returnVector.y += temp.y;
		}
	}

	return returnVector;
}

Vector Fan::getAttractedToArtistsVector() {
	Vector returnVector;

	for each (Artist* artist in artists)
	{
		Vector temp;
		temp.x += artist->currentTile->absoluteX + 10 - x;
		temp.y += artist->currentTile->absoluteY + 10 - y;

		double length = temp.getLength();
		double attracted_to_artist = chromosome.at("attracted_to_" + artist->name);

		if (length > attracted_to_artist) {
			temp.x = temp.x / length * attracted_to_artist;
			temp.y = temp.y / length * attracted_to_artist;
		}

		returnVector.x += temp.x;
		returnVector.y += temp.y;
	}


	return returnVector;
}

void Fan::move() {
	int correctionX = x + direction.x > x ? 4 : 0;
	int correctionY = y + direction.y > y ? 4 : 0;

	Tile * tileX = map->getTileByCoordinates(x + direction.x + correctionX, y + direction.y);
	Tile * tileY = map->getTileByCoordinates(x, y + direction.y + correctionY);

	bool canMoveX = tileX->type != '1' && tileX->type != '2' && tileX->type != '3' ? false : true;

	bool canMoveY = tileY->type != '1' && tileY->type != '2' && tileY->type != '3' ? false : true;

	if (!canMoveX) direction.x = 0;
	if (!canMoveY) direction.y = 0;

	x = x + direction.x;
	y = y + direction.y;
}

int Fan::getPointsForBeingNearArtists() {

	int returnValue = 0;

	for each (Artist* artist in artists)
	{
		if (x >= artist->currentTile->absoluteX - NEAR_ARTIST_RADIUS &&
			x <= artist->currentTile->absoluteX + artist->width + NEAR_ARTIST_RADIUS &&
			y >= artist->currentTile->absoluteY - NEAR_ARTIST_RADIUS &&
			y <= artist->currentTile->absoluteY + artist->heigth + NEAR_ARTIST_RADIUS
			) 
			returnValue++;
	}

	return returnValue;
}

bool Fan::checkIfDead() {	
	for each (Artist* artist in artists )
	{
		if (artist->hostile) {
			if (x >= artist->currentTile->absoluteX - 15 &&
				x <= artist->currentTile->absoluteX + artist->width + 15 &&
				y >= artist->currentTile->absoluteY - 15 &&
				y <= artist->currentTile->absoluteY + artist->heigth + 15) {
				return true;
			}
		}
	}

	return false;
}

void Fan::initRandomStartingValues() {

	chromosome.insert(std::make_pair("cohesion", (double)generateRandom(0, 100) / 100));
	chromosome.insert(std::make_pair("separation", ((double)generateRandom(0, 100) + 0) / 100));
	chromosome.insert(std::make_pair("alignment", (double)generateRandom(0, 100) / 100));

	for each (Artist* artist in artists)
	{
		chromosome.insert(std::make_pair("attracted_to_" + artist->name, (double)generateRandom(-100, 100) / 100));
	}
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


