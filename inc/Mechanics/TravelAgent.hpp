#pragma once

#include <GameMap/Planet.hpp>
#include <memory>
#include <iostream>

namespace Mechanics
{
class TravelAgent
{
public:
	TravelAgent(std::weak_ptr<GameMap::Planet>);

	TravelAgent(TravelAgent&&) = default;

	TravelAgent(const TravelAgent&) = delete;
	TravelAgent& operator=(const TravelAgent&) = delete;
	TravelAgent& operator=(TravelAgent&&) = delete;

	friend std::ostream& operator<< (std::ostream&, const TravelAgent&);

	void showTravelOptions() const;
	bool isEndPlanetReached() const;
	
	using TravelAgentActionCallback = float(TravelAgent::*)(std::size_t);
	float performActionOnSelf(TravelAgentActionCallback, std::size_t);
	
	float getCheapestTravelCost();
	float getTravelCost(std::size_t);
	float travelTo(std::size_t);

	using PlanetActionCallback = float(GameMap::Planet::*)(float);
	float performActionOnCurrentPlanet(PlanetActionCallback, float) const;

private:
	std::weak_ptr<GameMap::Planet> currentPlanet;
};
} // namespace Mechanics
