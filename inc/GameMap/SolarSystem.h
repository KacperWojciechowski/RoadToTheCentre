#pragma once

#include <GameMap/Planet.h>
#include <vector>
#include <memory>

namespace GameMap
{
class SolarSystem;

using SolarSystemPtr = std::shared_ptr<SolarSystem>;

class SolarSystem
{
private:
	struct CreationGuard {};

public:
	static SolarSystemPtr create(Time::GameTimeService&);

	SolarSystem(std::vector<PlanetPtr>&&, CreationGuard);

	SolarSystem(SolarSystem&&) = delete;
	SolarSystem(const SolarSystem&) = delete;
	SolarSystem& operator=(SolarSystem&&) = delete;
	SolarSystem& operator=(const SolarSystem&) = delete;

	friend std::ostream& operator<<(std::ostream&, const SolarSystem&);
	Planet& operator[](int planetIndex);
	std::size_t getPlanetCount();

private:
	const std::vector<PlanetPtr> planets;
};
} // namespace GameMap
