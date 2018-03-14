#include "Artist.h"



void Artist::Update(float deltaTime)
{
	mApplication->SetColor(Color(0, 0, 102, 255));
	mApplication->DrawCircle(currentTile->absoluteX + 10, currentTile->absoluteY + 10, 10, true);
}


Artist::Artist(Map * mapIn)
{
	map = mapIn; 
	currentTile = map->getTile(4, 7);
}

Artist::~Artist()
{
}
