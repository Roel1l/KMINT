#include <iostream>
#include <vector>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>
#include "Fan.h"
#include "Map.h"
#include "Artist.h"
#include "Globals.h"
#include "Manager.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

using namespace std;

int main(int args[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // leak dump enabled

	auto application = new FWApplication();
	if (!application->GetWindow()){ LOG("Couldn't create window..."); return EXIT_FAILURE; }

	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));

#pragma region Init

	Map* map = new Map();
	map->loadMap();
	map->initTileNeighbours();

	std::vector<Artist*> artists;

	for (int i = 0; i <= AMOUNT_OF_ARTISTS - 1; i++) {
		artists.push_back(new Artist(map));

		if (i == 0) {
			artists[i]->name = "Axel Tulp";
			artists[i]->setColor(Color(0, 0, 102, 255));
		}
		if (i == 1) {
			artists[i]->name = "Johnnie Smith";
			artists[i]->setColor(Color(0, 0, 31, 255));
			artists[i]->hostile = true;
		}
		if (i == 2) {
			artists[i]->name = "Andre Konijnes";
			artists[i]->setColor(Color(51, 255, 51, 255));
		}
		if (i == 3) {
			artists[i]->name = "Frans Sloper";
			artists[i]->setColor(Color(255, 255, 0, 255));
		}
	}

	Manager* manager = new Manager(map);
	manager->setColor(Color(255, 255, 255, 255));
	manager->artists = artists;
	for each (Artist* artist in artists) application->AddRenderable(artist);
	application->AddRenderable(manager);

#pragma endregion

#pragma region Fans

	std::vector<Fan*>* fans = new vector<Fan*>;

	if (AMOUNT_OF_ARTISTS > 3) {
		for (int i = AMOUNT_OF_FANS; i > 0; i--) {
			Fan* fan = new Fan(i, fans, map);
			fan->axel = artists[0];
			fan->johnnie = artists[1];
			fan->andre = artists[2];
			fan->frans = artists[3];

			fan->initRandomStartingValues();
			fan->spawn();

			fans->push_back(fan);
			application->AddRenderable(fan);
		}
	}
#pragma endregion

	uint32_t msTimeOfLastButtonPressed = 0;
	uint32_t msTimeOfLastButtonPeriodTick = 0;
	uint32_t msTimeBetweenPeriodTicks = 1000;

	int simulationNumber = 1;
	int periodNumber = 0;

	Tile* t = map->getTileByCoordinates(1066.3529116917155, 720.78243684678728);

	while (application->IsRunning())
	{
		application->StartTick();
		uint32_t msTimeCurrent = application->GetTimeSinceStartedMS();
		if (msTimeCurrent - msTimeOfLastButtonPeriodTick >= (double)msTimeBetweenPeriodTicks * GLOBAL_SPEED) {
			msTimeOfLastButtonPeriodTick = msTimeCurrent;
			periodNumber++;
		}

		std::string simulationText = "Simulation: " + std::to_string(simulationNumber);
		std::string periodText = " Period: " + std::to_string(periodNumber);
		std::string title = simulationText + periodText;

		application->setWindowTitle(title.c_str());

		if (SHOW_PATH) {
			for each (std::vector<Tile*> list in map->grid) for each (Tile* tile in list) tile->partOfPath = false;
			for (int i = 0; i < artists.size(); i++) 
			{
				if (i == 0 && SHOW_AXEL_PATH) for each (Tile* t in artists[i]->path) t->partOfPath = true;
				if (i == 1 && SHOW_JOHNNIE_PATH) for each (Tile* t in artists[i]->path) t->partOfPath = true;
				if (i == 2 && SHOW_ANDRE_PATH) for each (Tile* t in artists[i]->path) t->partOfPath = true;
				if (i == 3 && SHOW_FRANS_PATH) for each (Tile* t in artists[i]->path) t->partOfPath = true;
			}
			if(SHOW_MANAGER_PATH) for each (Tile* t in manager->path) t->partOfPath = true;
		}

#pragma region Handling Key Events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				application->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_PAGEUP:
					GLOBAL_SPEED += 0.1;
					break;
				case SDL_SCANCODE_PAGEDOWN:
					GLOBAL_SPEED = GLOBAL_SPEED <= 0 ? 0 : GLOBAL_SPEED - 0.1;
					break;
				case SDL_SCANCODE_P:
					if (application->GetTimeSinceStartedMS() - msTimeOfLastButtonPressed > 100) {
						SHOW_PATH = !SHOW_PATH;
						msTimeOfLastButtonPressed = application->GetTimeSinceStartedMS();
					}
					break;
				case SDL_SCANCODE_3:
					if (application->GetTimeSinceStartedMS() - msTimeOfLastButtonPressed > 100) {
						SHOW_ANDRE_PATH = !SHOW_ANDRE_PATH;
						msTimeOfLastButtonPressed = application->GetTimeSinceStartedMS();
					}
					break;
				case SDL_SCANCODE_1:
					if (application->GetTimeSinceStartedMS() - msTimeOfLastButtonPressed > 100) {
						SHOW_AXEL_PATH = !SHOW_AXEL_PATH;
						msTimeOfLastButtonPressed = application->GetTimeSinceStartedMS();
					}
					break;
				case SDL_SCANCODE_4:
					if (application->GetTimeSinceStartedMS() - msTimeOfLastButtonPressed > 100) {
						SHOW_FRANS_PATH = !SHOW_FRANS_PATH;
						msTimeOfLastButtonPressed = application->GetTimeSinceStartedMS();
					}
					break;
				case SDL_SCANCODE_2:
					if (application->GetTimeSinceStartedMS() - msTimeOfLastButtonPressed > 100) {
						SHOW_JOHNNIE_PATH = !SHOW_JOHNNIE_PATH;
						msTimeOfLastButtonPressed = application->GetTimeSinceStartedMS();
					}
					break;
				case SDL_SCANCODE_0:
					if (application->GetTimeSinceStartedMS() - msTimeOfLastButtonPressed > 100) {
						SHOW_MANAGER_PATH = !SHOW_MANAGER_PATH;
						msTimeOfLastButtonPressed = application->GetTimeSinceStartedMS();
					}
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			}
		}
#pragma endregion

		map->drawMap(application);
		application->UpdateGameObjects();
		application->RenderGameObjects();

		application->SetColor(Color(0, 0, 0, 255));
		for (int i = 0; i < artists.size(); i++) {
			application->DrawText(artists[i]->name + " money: " + std::to_string(artists[i]->money), 100, 740 + 20 * i);
		}

		application->DrawText("Simulation Speed: " + std::to_string(GLOBAL_SPEED), 400, 740);
		application->DrawText("Show Path (P): " + std::to_string(SHOW_PATH), 400, 760);

		application->SetColor(Color(255, 255, 255, 255));
		application->EndTick();
	}

	for each (Fan* fan in *fans) delete fan;
	delete fans;
	delete map;
	for each (Artist* artist in artists) delete artist;
	delete manager;
	delete application;

	//int* i = new int(23);
	return EXIT_SUCCESS;
}