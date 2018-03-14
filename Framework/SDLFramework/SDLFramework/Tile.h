#pragma once
#include <iostream>
#include <string>

class Tile
{
public:
	Tile(char typeIn) { type = typeIn; }
	~Tile();

	char type;
};

