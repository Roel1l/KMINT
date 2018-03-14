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
	application->AddRenderable(axel_tulp);

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

	while (application->IsRunning())
	{
		GLOBAL_ACTION_TIMER = GLOBAL_ACTION_TIMER >= GLOBAL_SPEED ? 0 : GLOBAL_ACTION_TIMER + 1;
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
					GLOBAL_SPEED--;
					LOG("GLOBAL_SPEED SET TO: " + std::to_string(GLOBAL_SPEED));
					break;
				case SDL_SCANCODE_PAGEDOWN:
					GLOBAL_SPEED++;
					LOG("GLOBAL_SPEED SET TO: " + std::to_string(GLOBAL_SPEED));
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

		//application->SetColor(Color(0, 0, 0, 255));
		//application->DrawText("Welcome to KMint", 400, 300);

		map->drawMap(application);

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}

	for each (Bird* var in *birds)
	{
		delete var;
	}
	delete birds;
	delete map;
	//delete axel_tulp;
	return EXIT_SUCCESS;
}