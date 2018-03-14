#pragma once
#include "IGameObject.h"
#include <SDL_render.h>
#include "Graph.h"

class GraphObject : public IGameObject
{
public:
	GraphObject(Graph* g);
	~GraphObject();
	void Update(float deltaTime);

	SDL_Texture *texture;

	Vertex* currentVertex;

private:
	Graph* graph;

};

