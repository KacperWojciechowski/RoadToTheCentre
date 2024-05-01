#pragma once

#include <GameMap/SolarSystem.h>
#include <TimeServices/GameTimeService.h>
#include <vector>
#include <iostream>

namespace GameMap
{
class Galaxy
{
private:
	using SystemLayer = std::vector<SolarSystemPtr>;
public:
	Galaxy(Time::GameTimeService&);

	SystemLayer& operator[](std::size_t layerIndex);
	friend std::ostream& operator<<(std::ostream& out, const Galaxy&);

private:
	const float interstellarTravelCost;
	std::vector<SystemLayer> layers;
};
}
