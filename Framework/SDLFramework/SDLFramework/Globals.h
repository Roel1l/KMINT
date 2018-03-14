#pragma once
#include <random>

#ifndef GLOBALS
#define GLOBALS
static int GLOBAL_ACTION_TIMER = 0;
static int GLOBAL_SPEED = 60.0;

static std::random_device rd;
static int generateRandom(int min, int max) {
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(min, max);

	auto random_integer = uni(rng);
	return random_integer;
}

#endif