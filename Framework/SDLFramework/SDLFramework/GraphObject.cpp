#include "GraphObject.h"
#include "Math.h"
#include <algorithm>

GraphObject::GraphObject(Graph* g)
{
	graph = g;
	currentVertex = g->vertices[1];


}


GraphObject::~GraphObject()
{

}

void GraphObject::Update(float deltaTime)
{
	mApplication->SetColor(Color(0, 0, 102, 255));
	mApplication->DrawCircle(currentVertex->x, currentVertex->y, 10, true);
//	SetOffset(currentVertex->x, currentVertex->y, 0);
}

