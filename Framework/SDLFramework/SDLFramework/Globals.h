#pragma once
#include <random>

// Simulation
const int AMOUNT_OF_SIMULATIONS = 5;
const int AMOUNT_OF_PERIODS_IN_SIMULATION = 100;

// Artists
const int AMOUNT_OF_ARTISTS = 4; 

// Fans
extern int LAST_FAN_ID;
const int AMOUNT_OF_FANS = 100;

const bool COHESION = true;
const double COHESION_RADIUS = 100;

const bool SEPARATION = true;
const double SEPARATION_RADIUS = 100;

const bool ALIGNMENT = true;
const double MIMIC_RADIUS = 100;

const bool STEERING = false;
const double STEER_INTENSITY = 0.05;

const bool STAY_NEAR_ARTISTS = true;
const double NEAR_ARTIST_RADIUS = 30;

extern bool SHOW_FAN_STATS;

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
const int SCREEN_HEIGTH = 720;

// Functions
static std::random_device rd;
static int generateRandom(int min, int max) {
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(min, max);

	auto random_integer = uni(rng);
	return random_integer;
}