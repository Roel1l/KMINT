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
#include <algorithm>
#include "Genetics.h"

using namespace std;

uint32_t msTimeOfLastButtonPressed = 0;
uint32_t msTimeOfLastButtonPeriodTick = 0;
uint32_t msTimeBetweenPeriodTicks = 500;

int simulationNumber = 1;
int periodNumber = 0;

FWApplication* application;

bool canPressButton() {
	if (application->GetTimeSinceStartedMS() - msTimeOfLastButtonPressed > 100) {
		msTimeOfLastButtonPressed = application->GetTimeSinceStartedMS();
		return true;
	}
	return false;
}

int main(int args[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // leak dump enabled

	application = new FWApplication();
	if (!application->GetWindow()) { LOG("Couldn't create window..."); return EXIT_FAILURE; }

	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));

#pragma region Init

	Map* map = new Map();
	map->loadMap();
	map->initTileNeighbours();

	std::vector<Artist*> artists;

	for (int i = 0; i <= AMOUNT_OF_ARTISTS - 1; i++) {
		artists.push_back(new Artist(map));
		artists[i]->spawn();

		if (i == 0) {
			artists[i]->name = "Axel_Tulp";
			artists[i]->setColor(Color(0, 0, 102, 255));
		}
		else if (i == 1) {
			artists[i]->name = "Johnnie_Smith";
			artists[i]->setColor(Color(0, 0, 31, 255));
			artists[i]->hostile = true;
		}
		else if (i == 2) {
			artists[i]->name = "Andre_Konijnes";
			artists[i]->setColor(Color(51, 255, 51, 255));
		}
		else if (i == 3) {
			artists[i]->name = "Frans_Sloper";
			artists[i]->setColor(Color(255, 255, 0, 255));
		}
		else {
			artists[i]->name = "Artist_" + std::to_string(i);
		}
	}

	Manager* manager = new Manager(map);
	manager->setColor(Color(255, 255, 255, 255));
	manager->artists = artists;
	manager->spawn();

	for each (Artist* artist in artists) application->AddRenderable(artist);
	application->AddRenderable(manager);

#pragma endregion

#pragma region Fans

	std::vector<Fan*>* fans = new vector<Fan*>;

	for (int i = AMOUNT_OF_FANS; i > 0; i--) {

		LAST_FAN_ID++;

		Fan* fan = new Fan(LAST_FAN_ID, fans, map, artists);

		fan->initRandomStartingValues();
		fan->spawn();

		fans->push_back(fan);
		application->AddRenderable(fan);
	}

#pragma endregion

	int fanInfoIterator = 0;

	while (application->IsRunning())
	{
		if (periodNumber < AMOUNT_OF_PERIODS_IN_SIMULATION) {
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
				if (SHOW_MANAGER_PATH) for each (Tile* t in manager->path) t->partOfPath = true;
			}

			SDL_Event event;
			if (canPressButton()) {
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
							SHOW_PATH = !SHOW_PATH;
							break;
						case SDL_SCANCODE_3:
							SHOW_ANDRE_PATH = !SHOW_ANDRE_PATH;
							break;
						case SDL_SCANCODE_1:
							SHOW_AXEL_PATH = !SHOW_AXEL_PATH;
							break;
						case SDL_SCANCODE_4:
							SHOW_FRANS_PATH = !SHOW_FRANS_PATH;
							break;
						case SDL_SCANCODE_2:
							SHOW_JOHNNIE_PATH = !SHOW_JOHNNIE_PATH;
							break;
						case SDL_SCANCODE_0:
							SHOW_MANAGER_PATH = !SHOW_MANAGER_PATH;
							break;
						case SDL_SCANCODE_I:
							SHOW_FAN_STATS = !SHOW_FAN_STATS;
							break;
						case SDL_SCANCODE_RIGHT:
							fanInfoIterator = fanInfoIterator < fans->size() - 1 ? fanInfoIterator + 1 : 0;
							break;
						case SDL_SCANCODE_LEFT:
							fanInfoIterator = fanInfoIterator > 0 ? fanInfoIterator - 1 : fans->size() - 1;
							break;
						default:
							break;
						}
						break;
					case SDL_MOUSEBUTTONDOWN:
						break;
					}
				}
			}
			
			map->drawMap(application);
			application->UpdateGameObjects();
			application->RenderGameObjects();

			application->SetColor(Color(255, 255, 255, 255));
			for (int i = 0; i < artists.size(); i++) {
				application->DrawText(artists[i]->name + ": " + std::to_string(artists[i]->money), 100 + 300 * i, 10);
			}

			if (SHOW_FAN_STATS) {
				application->DrawRect(SCREEN_WIDTH - 200, SCREEN_HEIGTH - 300, 200, 300, true);
				application->SetColor(Color(0, 0, 0, 255));

				std::string populationSize = "current population size: " + std::to_string(fans->size());

				std::string fanId = "ID: " + std::to_string(fans->at(fanInfoIterator)->id);
				std::string fanFitness = "fitness: " + std::to_string(fans->at(fanInfoIterator)->fitness);
				std::string fanDied = fans->at(fanInfoIterator)->dead ? "dead: yes" : "dead: no";

				int counter = 0;

				application->DrawText(populationSize, SCREEN_WIDTH - 100, SCREEN_HEIGTH - 290 + counter * 15);
				counter++; counter++;

				application->DrawText("----Fan----", SCREEN_WIDTH - 100, SCREEN_HEIGTH - 290 + counter * 15);
				counter++;
				application->DrawText(fanId, SCREEN_WIDTH - 100, SCREEN_HEIGTH - 290 + counter * 15);
				counter++;
				application->DrawText(fanFitness, SCREEN_WIDTH - 100, SCREEN_HEIGTH - 290 + counter * 15);
				counter++;
				application->DrawText(fanDied, SCREEN_WIDTH - 100, SCREEN_HEIGTH - 290 + counter * 15);
				counter++; counter++;

				application->DrawText("--Chromosome--", SCREEN_WIDTH - 100, SCREEN_HEIGTH - 290 + counter * 15);
				counter++;

				for (auto const& chromosomeBit : fans->at(fanInfoIterator)->chromosome) {
					
					std::string info = chromosomeBit.first + ": " + std::to_string(chromosomeBit.second).substr(0, 4);
					application->DrawText(info, SCREEN_WIDTH - 100, SCREEN_HEIGTH - 290 + counter * 15);

					counter++;
				}

			}

			application->EndTick();
		}
		else {
			Genetics g;
			std::vector<Fan*> newPopulation = g.fitness_proportionate_selection(*fans);

			for each (Fan* fan in *fans) {
				application->RemoveRenderable(fan);
				delete fan;
			}
			fans->clear();

			for each (Fan* fan in newPopulation)
			{
				fans->push_back(fan);
				fan->spawn();
				application->AddRenderable(fan);
			}

			for each (Artist* artist in artists) artist->spawn();

			manager->spawn();

			fanInfoIterator = 0;
			periodNumber = 0;
			simulationNumber++;
		}
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