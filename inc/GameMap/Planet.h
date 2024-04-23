#pragma once

#include <iostream>
#include <random>
#include <TimeServices/GameTimeService.h>

namespace GameMap
{
class Planet : public Time::ITimeObserver, public std::enable_shared_from_this<Planet>
{
	struct CreationGuard {};

public:
	static std::shared_ptr<Planet> create(int starId, Time::GameTimeService&);

	Planet(int starId, CreationGuard);

	Planet(const Planet&) = delete;
	Planet(Planet&&) = delete;
	Planet& operator=(const Planet&) = delete;
	Planet& operator=(Planet&&) = delete;

	friend std::ostream& operator<<(std::ostream&, const Planet&);

	void tick() override;

	float getSpiceSellCost();
	float getSpiceBuyCost();
	float buySpice(float amount);
private:
	using RandomEngine = std::mt19937;

	void generatePlanetId(RandomEngine&);
	void generateSpiceInfo(RandomEngine&);
	void generatePrices(RandomEngine&);
	void generateCycleInfo(RandomEngine&);

	int starId = {};
	int planetId = {};
	float spiceCapacity = {};
	float spiceInStock = {};
	float spiceBuyCost = {};
	float spiceSellCost = {};
	int refreshPeriod = {};
	int cyclesUntilRefresh = {};
};
} // namespace GameMap
