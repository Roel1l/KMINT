#include <iostream>
#include <vector>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>
#include "Bird.h"
#include "FlockingGlobals.h"
#include "Map.h"
#include "Artist.h"
#include "Globals.h"

using namespace std;

int main(int args[])
{
	auto application = new FWApplication();
	if (!application->GetWindow()){ LOG("Couldn't create window..."); return EXIT_FAILURE; }

	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));

	Map* map = new Map();
	map->loadMap();
	map->initTileNeighbours();
	
	Artist* axel_tulp = new Artist(map);
	Artist* frans_sloper = new Artist(map);
	Artist* manager = new Artist(map);

	axel_tulp->setColor(Color(0, 0, 102, 255));
	frans_sloper->setColor(Color(255, 255, 0, 255));
	manager->setColor(Color(0, 255, 255, 255));

	application->AddRenderable(manager);
	application->AddRenderable(axel_tulp);
	application->AddRenderable(frans_sloper);

#pragma region Fans
	std::vector<Bird*>* birds = new vector<Bird*>;
	int lastId = 0;

	for (int i = AMOUNT_OF_BIRDS; i > 0; i--) {
		Bird* bird = new Bird(i, birds);
		birds->push_back(bird);
		application->AddRenderable(bird);
		lastId++;
	}

#pragma endregion

	uint32_t msTimeOfLastButtonPressed = 0;

	while (application->IsRunning())
	{
		application->StartTick();

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
		application->DrawText("Money Axel Tulp: " + std::to_string(axel_tulp->money), 100, 740);
		application->DrawText("Money Frans Sloper: " + std::to_string(frans_sloper->money), 100, 760);
		application->DrawText("Money Johnnie Smith: " + std::to_string(0), 100, 780);
		application->DrawText("Money André Konijnes: " + std::to_string(0), 100, 800);

		application->DrawText("Simulation Speed: " + std::to_string(GLOBAL_SPEED), 400, 740);
		application->DrawText("Show Path (P): " + std::to_string(SHOW_PATH), 400, 760);

		application->SetColor(Color(255, 255, 255, 255));
		application->EndTick();
	}

	for each (Bird* var in *birds)
	{
		delete var;
	}
	delete birds;
	delete map;
	delete axel_tulp;
	delete frans_sloper;
	delete manager;
	return EXIT_SUCCESS;
}