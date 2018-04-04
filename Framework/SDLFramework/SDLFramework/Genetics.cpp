#include "Genetics.h"



Genetics::Genetics()
{
}


Genetics::~Genetics()
{
}

int Genetics::rouletteSelect(vector<double> fitnesses) {
	// calculate the total weight
	double fitness_sum = 0;
	for (int i = 0; i<fitnesses.size(); i++) {
		fitness_sum += fitnesses[i];
	}
	// get a random value
	double value = ((double)generateRandom(0, 100) / 100) * fitness_sum;
	// locate the random value based on the weights
	for (int i = 0; i<fitnesses.size(); i++) {
		value -= fitnesses[i];
		if (value < 0) return i;
	}
	// when rounding errors occur, we return the last item's index 
	return fitnesses.size() - 1;
}

Fan* Genetics::getChild(Fan* parentOne, Fan* parentTwo) {
	
	LAST_FAN_ID++;
	Fan * child = new Fan(LAST_FAN_ID, parentOne->fans, parentOne->map, parentOne->artists);

	int separationIndex = generateRandom(0, parentOne->chromosome.size() - 1);

	for (int i = 0; i < parentOne->chromosome.size(); i++)
	{
		Fan * inheritParent = i <= separationIndex ? parentOne : parentTwo;


	}

	int counter = 0;

	for (auto const& chromosomeBit : parentOne->chromosome) {

		if (counter <= separationIndex) child->chromosome.insert(chromosomeBit);
		else child->chromosome.insert(std::make_pair(chromosomeBit.first, parentTwo->chromosome.at(chromosomeBit.first)));
		
		counter++;
	}

	return child;
}

std::vector<Fan*> Genetics::fitness_proportionate_selection(std::vector<Fan*> population) {

	std::sort(population.begin(), population.end(),
		[](Fan* const & a, Fan* const & b) -> bool
	{ return a->fitness > b->fitness; });

	std::vector<Fan*> newPopulation;

	for (size_t counter = 0; counter < population.size() / 3 * 2; counter++)
	{
		std::vector<Fan*> tempPopulation(population.begin(), population.end());
		std::vector<double> fitnesses;

		for (int i = 0; i < tempPopulation.size(); i++) fitnesses.push_back((double)tempPopulation[i]->fitness);

		Fan* chosenIndividualOne = tempPopulation.at(rouletteSelect(fitnesses));
		tempPopulation.erase(std::remove(tempPopulation.begin(), tempPopulation.end(), chosenIndividualOne));

		fitnesses.clear();

		for (int i = 0; i < tempPopulation.size(); i++) fitnesses.push_back((double)tempPopulation[i]->fitness);

		Fan* chosenIndividualTwo = tempPopulation.at(rouletteSelect(fitnesses));

		newPopulation.push_back(getChild(chosenIndividualOne, chosenIndividualTwo));
	}

	return newPopulation;
}