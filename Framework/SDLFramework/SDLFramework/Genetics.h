#pragma once
#include "Globals.h"
#include <vector>
#include "Fan.h"
#include <algorithm>

using namespace std;

class Genetics
{
public:
	Genetics();
	~Genetics();
	std::vector<Fan*> fitness_proportionate_selection(std::vector<Fan*> population);
private:
	int rouletteSelect(vector<double> fitnesses);
	Fan * getChild(Fan * parentOne, Fan * parentTwo);
};

