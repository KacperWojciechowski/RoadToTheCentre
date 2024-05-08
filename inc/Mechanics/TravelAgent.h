#pragma once

#include <GameMap/Planet.h>
#include <memory>

namespace Mechanics
{
class TravelAgent
{
public:
	TravelAgent(std::weak_ptr<GameMap::Planet>);

	TravelAgent(const TravelAgent&) = delete;
	TravelAgent(TravelAgent&&) = delete;
	TravelAgent& operator=(const TravelAgent&) = delete;
	TravelAgent& operator=(TravelAgent&&) = delete;

	void printCurrentPlanetData();
	void showTravelOptions();
	float travelTo(std::size_t);
	bool isEndPlanetReached();

	using PlanetActionCallback = float(GameMap::Planet::*)(float);
	float performPlanetAction(PlanetActionCallback, float);

private:
	GameMap::PlanetPtr validatePlanet();
	std::weak_ptr<GameMap::Planet> currentPlanet;
};
} // namespace Mechanics
