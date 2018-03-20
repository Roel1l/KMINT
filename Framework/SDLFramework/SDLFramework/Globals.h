#pragma once
#include <random>

const int AMOUNT_OF_ARTISTS = 4; // Max = 4;
const int AMOUNT_OF_FANS = 100;

// Game speed
extern double GLOBAL_SPEED;

// Pathing
extern bool SHOW_PATH;
extern bool SHOW_AXEL_PATH;
extern bool SHOW_FRANS_PATH;
extern bool SHOW_JOHNNIE_PATH;
extern bool SHOW_ANDRE_PATH;
extern bool SHOW_MANAGER_PATH;

// Screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGTH = 820;

// Functions
static std::random_device rd;
static int generateRandom(int min, int max) {
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(min, max);

	auto random_integer = uni(rng);
	return random_integer;
}
