#include "Genetics.h"



Genetics::Genetics()
{
}


Genetics::~Genetics()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Creates a new population using fitness proportionate selection. (https://en.wikipedia.org/wiki/Fitness_proportionate_selection) </summary>
///
/// <remarks>	Roel Guerand, 04-04-2018. </remarks>
///
/// <returns>	A new population of fans 2/3ths the size of the input population </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Fan*> Genetics::fitness_proportionate_selection(std::vector<Fan*> population) {

	// sort current population from fittest to least fittest;
	std::sort(population.begin(), population.end(),
		[](Fan* const & a, Fan* const & b) -> bool
	{ return a->fitness > b->fitness; });

	std::vector<Fan*> newPopulation;

	// Start choosing pairs of individuals to create children. Create 2/3ths of the current population as a new one
	int newPopulationSize = population.size() <= 18 ? 18 : population.size() / 3 * 2;

	for (size_t counter = 0; counter < newPopulationSize; counter++)
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Chooses a random fitnes out of a list of fitnesses. With the higher fitnesses having a higher chance to be selected. Like a roulette wheel  </summary>
///
/// <remarks>	Roel Guerand, 04-04-2018. </remarks>
///
/// <returns>	Index of chosen fitness </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
int Genetics::rouletteSelect(vector<double> fitnesses) {
	// calculate the total fitness
	double fitness_sum = 0;
	for (int i = 0; i<fitnesses.size(); i++) {
		fitness_sum += fitnesses[i];
	}
	// get a random value
	double value = ((double)generateRandom(0, 100) / 100) * fitness_sum;
	// locate the random value based on the fitnesses
	for (int i = 0; i<fitnesses.size(); i++) {
		value -= fitnesses[i];
		if (value < 0) return i;
	}
	// when rounding errors occur, we return the last item's index 
	return fitnesses.size() - 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Uses 2 fans to create a new fan by combining the chromosomes </summary>
///
/// <remarks>	Roel Guerand, 04-04-2018. </remarks>
///
/// <returns>	The newly created child (Fan) </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
Fan* Genetics::getChild(Fan* parentOne, Fan* parentTwo) {

	LAST_FAN_ID++;
	// create a new fan
	Fan * child = new Fan(LAST_FAN_ID, parentOne->fans, parentOne->map, parentOne->artists);

	// choose random index to split the chromosome on
	int separationIndex = generateRandom(0, parentOne->chromosome.size() - 1);

	int counter = 0;

	// copy the chromosomes of the parents into the child chromosome using the separationIndex as division point between what parent to use.
	for (auto const& chromosomeBit : parentOne->chromosome) {

		if (counter <= separationIndex) child->chromosome.insert(chromosomeBit);
		else child->chromosome.insert(std::make_pair(chromosomeBit.first, parentTwo->chromosome.at(chromosomeBit.first)));

		counter++;
	}

	return child;
}