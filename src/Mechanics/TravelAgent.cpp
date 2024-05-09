#include <Mechanics/TravelAgent.h>
#include <iostream>

namespace
{
GameMap::PlanetPtr validate(std::weak_ptr<GameMap::Planet> planet)
{
	auto planetPtr = planet.lock();
	if (not planetPtr)
	{
		throw std::runtime_error("currentPlanet points to a dead object");
	}
	return planetPtr;
}
} // namespace

namespace Mechanics
{
	TravelAgent::TravelAgent(std::weak_ptr<GameMap::Planet> planetPtr)
		: currentPlanet(std::move(planetPtr))
	{
	}

	void TravelAgent::printCurrentPlanetData()
{
	auto planet = validate(currentPlanet);
	std::cout << "== Current planet data: ==\n";
	std::cout << *planet << std::flush;
}

void TravelAgent::showTravelOptions()
{
	auto planet = validate(currentPlanet);
	std::cout << "== Travel options: ==\n";
	planet->printAdjacencyPlanetsInfo(std::cout);
}

float TravelAgent::travelTo(std::size_t adjPlanetIdx)
{
	auto currPlanet = validate(currentPlanet);
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
	auto planet = validate(currentPlanet);
	return planet->isEndPlanet();
}
float TravelAgent::performActionOnCurrentPlanet(PlanetActionCallback action, float amount)
{
	auto planet = validate(currentPlanet);
	return ((*planet).*action)(amount);
}
} // namespace Mechanics
