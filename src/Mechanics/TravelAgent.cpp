#include <Mechanics/TravelAgent.h>
#include <iostream>

namespace Mechanics
{
void TravelAgent::printCurrentPlanetData()
{
	auto planet = validatePlanet();
	std::cout << "== Current planet data: ==\n";
	std::cout << *planet << std::flush;
}

void TravelAgent::showTravelOptions()
{
	auto planet = validatePlanet();
	std::cout << "== Travel options: ==\n";
	planet->printAdjacencyPlanetsInfo(std::cout);
}

float TravelAgent::travelTo(std::size_t adjPlanetIdx)
{
	auto currPlanet = validatePlanet();
	auto adjPlanetInfo = currPlanet->getAdjacentPlanetInfo(adjPlanetIdx);
	
	if (not adjPlanetInfo.adjPlanet.lock())
	{
		throw std::runtime_error("adjPlanetInfo points to dead planet");
	}
	currentPlanet = adjPlanetInfo.adjPlanet;
	return adjPlanetInfo.travelCost;
}

bool TravelAgent::isEndPlanetReached()
{
	auto planet = validatePlanet();
	return planet->isEndPlanet();
}
float TravelAgent::performPlanetAction(PlanetActionCallback action, float amount)
{
	auto planet = validatePlanet();
	return ((*planet).*action)(amount);
}
GameMap::PlanetPtr TravelAgent::validatePlanet()
{
	auto planet = currentPlanet.lock();
	if (not planet)
	{
		throw std::runtime_error("currentPlanet points to a dead object");
	}
	return planet;
}
} // namespace Mechanics
