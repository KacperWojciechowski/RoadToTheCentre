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
	using iterator = std::vector<PlanetPtr>::iterator;
	using const_iterator = std::vector<PlanetPtr>::const_iterator;

	static SolarSystemPtr create(Time::GameTimeService&);

	SolarSystem(std::vector<PlanetPtr>&&, CreationGuard);

	SolarSystem(SolarSystem&&) = delete;
	SolarSystem(const SolarSystem&) = delete;
	SolarSystem& operator=(SolarSystem&&) = delete;
	SolarSystem& operator=(const SolarSystem&) = delete;

	const_iterator begin();
	const_iterator end();

	friend std::ostream& operator<<(std::ostream&, const SolarSystem&);
	PlanetPtr operator[](int planetIndex);
	
	std::size_t getPlanetCount() const;
	float getInterplanetaryTravelCost() const;

private:
	void interconnectPlanets();

	float interplanetaryTravelCost;
	const std::vector<PlanetPtr> planets;
};
} // namespace GameMap