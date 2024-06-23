#include <Mechanics/TravelAgent.hpp>
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

void TravelAgent::showTravelOptions() const
{
	auto planet = validate(currentPlanet);
	std::cout << "================= Travel options: =================\n";
	planet->printAdjacencyPlanetsInfo(std::cout);
}

float TravelAgent::performActionOnSelf(TravelAgentActionCallback action, std::size_t context)
{
	if (not action)
	{
		return 0.0f;
	}
	return (this->*action)(context);
}

float TravelAgent::getCheapestTravelCost()
{
	auto cheapestTravelCost = getTravelCost(0);
	auto currPlanet = validate(currentPlanet);

	constexpr float dummyContext = 0.0f;
	for (std::size_t i = 1; i < currPlanet->getAdjacentPlanetCount(dummyContext); i++)
	{
		auto travelCost = getTravelCost(i);
		if (travelCost < cheapestTravelCost)
		{
			cheapestTravelCost = travelCost;
		}
	}
	return cheapestTravelCost;
}

float TravelAgent::getTravelCost(std::size_t adjPlanetIdx)
{
	auto currPlanet = validate(currentPlanet);
	auto adjPlanetInfo = currPlanet->getAdjacentPlanetInfo(adjPlanetIdx);

	if (not adjPlanetInfo.adjPlanet.lock())
	{
		throw std::runtime_error("adjPlanetInfo points to dead planet");
	}
	return adjPlanetInfo.travelCost;
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

bool TravelAgent::isEndPlanetReached() const
{
	auto planet = validate(currentPlanet);
	return planet->isEndPlanet();
}

float TravelAgent::performActionOnCurrentPlanet(PlanetActionCallback action, float amount) const
{
	if (not action)
	{
		return 0.0f;
	}
	auto planet = validate(currentPlanet);
	return (planet.get()->*action)(amount);
}

std::ostream& operator<<(std::ostream& out, const TravelAgent& travelAgent)
{
	auto planet = validate(travelAgent.currentPlanet);
	out << "== Current planet data: ==\n";
	out << *planet << std::flush;
	return out;
}
} // namespace Mechanics
