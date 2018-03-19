#pragma once
#include <random>

extern double GLOBAL_SPEED;
extern bool SHOW_PATH;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGTH = 820;

static std::random_device rd;
static int generateRandom(int min, int max) {
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(min, max);

	auto random_integer = uni(rng);
	return random_integer;
}
