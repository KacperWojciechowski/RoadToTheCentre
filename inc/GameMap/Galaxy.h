#pragma once

#include <GameMap/SolarSystem.h>
#include <Services/GameTimeService.h>
#include <vector>
#include <iostream>

namespace GameMap
{
class Galaxy
{
public:
	using SystemLayer = std::vector<SolarSystemPtr>;

	Galaxy(Time::GameTimeService&);

	SystemLayer& operator[](std::size_t);
	friend std::ostream& operator<<(std::ostream&, const Galaxy&);

private:
	std::vector<SystemLayer> layers;
};
}
