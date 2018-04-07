#include "Tile.h"

Tile::~Tile()
{
}

double Tile::weight()
{
	switch (type) {
	case '1': return 1.0;
	case '2': return 2.0;
	case '3': return 8.0;
	case 'L': return 3.0;
	case 'N': return 3.0;
	case 'P': return 3.0;
	case 'C': return 3.0;
	default: 1.0;
	}
}

bool Tile::traversable()
{
	switch (type) {
	case 'B': return false;
	default: return true;
	}
}

Color Tile::color()
{
	if(partOfPath && SHOW_PATH) return Color(0, 0, 0, 255);
	if(visitedByAlgorithm && SHOW_PATH) return Color(255, 0, 0, 255);

	switch (type) {
	case 'B': return Color(47, 79, 79, 255);
	case '1': return Color(211, 211, 211, 255);
	case '2': return Color(149, 143, 121, 255);
	case '3': return Color(141, 0, 0, 255);
	case 'L': return Color(153, 0, 0, 255);
	case 'N': return Color(0, 128, 0, 255);
	case 'P': return Color(0, 0, 255, 255);
	case 'C': return Color(128, 0, 128, 255);
	default: return Color(0, 0, 0, 255);
	}
}

int Tile::getPayOut()
{
	switch (type) {
	case 'L': return generateRandom(200, 300);
	case 'N': return generateRandom(500, 700);
	case 'P': return 500;
	case 'C': return generateRandom(300, 1000);
	default: return 0;
	}
}
