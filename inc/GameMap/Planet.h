#pragma once

#include <iostream>
#include <random>
#include <TimeServices/GameTimeService.h>

namespace GameMap
{
class Planet;

using PlanetPtr = std::shared_ptr<Planet>;

class Planet : public Time::ITimeObserver, public std::enable_shared_from_this<Planet>
{
	struct CreationGuard {};

public:
	static PlanetPtr create(int starId, Time::GameTimeService&);

	Planet(int starId, CreationGuard);

	Planet(const Planet&) = delete;
	Planet(Planet&&) = delete;
	Planet& operator=(const Planet&) = delete;
	Planet& operator=(Planet&&) = delete;

	bool operator==(const Planet&);

	friend std::ostream& operator<<(std::ostream&, const Planet&);

	void tick() override;

	void connectIntraSystemPlanet(std::weak_ptr<Planet>, float);
	void connectInterStelarPlanet(std::weak_ptr<Planet>, float);

	float getSpiceSellCost() const;
	float getSpiceBuyCost() const;
	float buySpice(float amount);

private:
	enum class AdjacencyType
	{
		intraSystem,
		interStelar
	};

	struct AdjacencyInfo
	{
		std::weak_ptr<Planet> adjPlanet;
		AdjacencyType adjType;
		float travelCost;
	};
	
	void addAdjacentPlanet(std::weak_ptr<Planet>, AdjacencyType, float);

	const int starId = {};
	const int planetId = {};
	const float spiceCapacity = {};
	const float spiceBuyCost = {};
	const float spiceSellCost = {};
	const int refreshPeriod = {};
	
	float spiceInStock = {};
	int cyclesUntilRefresh = {};

	std::vector<AdjacencyInfo> adjacentPlanets;
};
} // namespace GameMap
