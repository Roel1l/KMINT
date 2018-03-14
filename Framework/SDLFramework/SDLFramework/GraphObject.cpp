#include "GraphObject.h"
#include "Math.h"
#include <algorithm>

GraphObject::GraphObject(Graph* g)
{
	graph = g;
	currentVertex = g->vertices[1];
	texture = mApplication->LoadTexture("lemmling_Cartoon_cow.png");
	this->SetTexture(texture);
	this->SetSize(30, 30);
}


GraphObject::~GraphObject()
{
	SDL_DestroyTexture(texture);
}

void GraphObject::Update(float deltaTime)
{
	SetOffset(currentVertex->x, currentVertex->y, 0);
}

