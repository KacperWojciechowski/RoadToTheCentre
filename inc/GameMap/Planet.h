#pragma once

#include <iostream>
#include <random>
#include <TimeServices/GameTimeService.h>

namespace GameMap
{
class Planet;

using PlanetPtr = std::shared_ptr<Planet>;

class Planet : public Time::ITimeObserver
{
	struct CreationGuard {};

public:
	static PlanetPtr create(int starId, Time::GameTimeService&);

	Planet(int starId, CreationGuard);

	Planet(const Planet&) = delete;
	Planet(Planet&&) = delete;
	Planet& operator=(const Planet&) = delete;
	Planet& operator=(Planet&&) = delete;

	friend std::ostream& operator<<(std::ostream&, const Planet&);

	void tick() override;

	float getSpiceSellCost() const;
	float getSpiceBuyCost() const;
	float buySpice(float amount);
private:
	const int starId = {};
	const int planetId = {};
	const float spiceCapacity = {};
	const float spiceBuyCost = {};
	const float spiceSellCost = {};
	const int refreshPeriod = {};
	
	float spiceInStock = {};
	int cyclesUntilRefresh = {};
};
} // namespace GameMap
