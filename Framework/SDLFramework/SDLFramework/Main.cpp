#include <iostream>
#include <vector>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>
#include "Bird.h"
#include "FlockingGlobals.h"
#include "Graph.h"
#include "GraphObject.h"

using namespace std;

int main(int args[])
{
	//auto window = Window::CreateSDLWindow();
	auto application = new FWApplication();
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}

	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));

	#pragma region Flocking
	std::vector<Bird*>* birds = new vector<Bird*>;
	int lastId = 0;

	for (int i = AMOUNT_OF_BIRDS; i > 0; i--) {
		Bird* bird = new Bird(i, birds);
		birds->push_back(bird);
		application->AddRenderable(bird);
		lastId++;
	}
	#pragma endregion

	#pragma region Pathfinding
	Graph* graph = new Graph();
	graph->init();

	GraphObject* example = new GraphObject(graph);
	application->AddRenderable(example);
	#pragma endregion

	std::vector<Vertex*> path = graph->findPath(graph->vertices[0], graph->vertices[graph->vertices.size() - 1]);

	while (application->IsRunning())
	{
		application->StartTick();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				application->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				/*if (event.button.button == 1) {
					int mouseX = 0;
					int mouseY = 0;
					SDL_GetMouseState(&mouseX, &mouseY);
	
					Bird* bird = new Bird(lastId + 1, birds, mouseX, mouseY);
					birds->push_back(bird);
					application->AddRenderable(bird);
					lastId++;
				}*/
				break;
			}
		}

		//application->SetColor(Color(0, 0, 0, 255));
		//application->DrawText("Welcome to KMint", 400, 300);

		#pragma region Pathfinding

			if (path.size() > 0) {
				example->currentVertex = path[0];
				path.erase(path.begin());
			}
		

		for (auto const& vertice : graph->vertices) {
			if (std::find(path.begin(), path.end(), vertice) != path.end()) {
				application->SetColor(Color(255, 0, 0, 255));
			}
			else {
				application->SetColor(Color(0, 0, 255, 255));
			}
			application->DrawCircle(vertice->x, vertice->y, 5, true);
		}

		#pragma endregion


		//// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}

	for each (Bird* var in *birds)
	{
		delete var;
	}
	delete birds;
	delete graph;
	return EXIT_SUCCESS;
}