#pragma once

#include <GameMap/SolarSystem.h>
#include <TimeServices/GameTimeService.h>
#include <vector>
#include <iostream>

namespace GameMap
{
class Galaxy
{
public:
	using SystemLayer = std::vector<SolarSystemPtr>;

	Galaxy(Time::GameTimeService&);

	SystemLayer& operator[](std::size_t layerIndex);
	friend std::ostream& operator<<(std::ostream& out, const Galaxy&);

private:
	std::vector<SystemLayer> layers;
};
}
