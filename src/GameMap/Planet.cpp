#include <GameMap/Planet.h>
#include <random>
#include <cassert>

namespace GameMap
{
std::ostream& operator<<(std::ostream& out, const Planet& planet)
{
	out << "[" << std::hex << planet.starId << "-" << planet.planetId << std::dec << "] {\n";
	out << "\tspices stock = " << planet.spiceInStock << "/" << planet.spiceCapacity << " tons\n";
	out << "\tpricing [buy/sell] = " << planet.spiceBuyCost << "/" << planet.spiceSellCost << "blix\n";
	out << "\ttime until refresh = " << planet.cyclesUntilRefresh << "\n}\n";
	return out; 
}

Planet::Planet(int starId, CreationGuard) : starId{starId}
{
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());

	generatePlanetId(gen);
	generateSpiceInfo(gen);
	generatePrices(gen);
	generateCycleInfo(gen);
}

std::shared_ptr<Planet> Planet::create(int starId, Time::GameTimeService& gameTimeService)
{
	auto planet = std::make_shared<Planet>(starId, CreationGuard{});
	gameTimeService.subscribe(planet);

	return planet;
}

void Planet::tick()
{
	if (spiceInStock != spiceCapacity)
	{
		cyclesUntilRefresh--;
	}
	if (cyclesUntilRefresh == 0)
	{
		spiceInStock = spiceCapacity;
		cyclesUntilRefresh = refreshPeriod;
	}
}

float Planet::getSpiceSellCost()
{
	return spiceSellCost;
}

float Planet::getSpiceBuyCost()
{
	return spiceBuyCost;
}

float Planet::buySpice(float amount)
{
	assert(amount <= spiceInStock);

	spiceInStock -= amount;

	return amount * spiceBuyCost;
}

void Planet::generatePlanetId(RandomEngine& engine)
{
	constexpr auto lowerIdBound = 0x01000000;
	constexpr auto upperIdBound = 0x0FFFFFFF;
	std::uniform_int_distribution<> distribution(lowerIdBound, upperIdBound);
	planetId = distribution(engine);
}

void Planet::generateSpiceInfo(RandomEngine& engine)
{
	constexpr auto lowerSpiceStockBound = 10.0;
	constexpr auto upperSpiceStockBound = 50.0;
	std::uniform_real_distribution<> distribution(lowerSpiceStockBound, upperSpiceStockBound);
	spiceCapacity = static_cast<float>(distribution(engine));
	spiceInStock = spiceCapacity;
}

void Planet::generatePrices(RandomEngine& engine)
{
	constexpr auto lowerBasePriceRange = 50.0;
	constexpr auto upperBasePriceRange = 300.0;
	std::uniform_real_distribution<> buyPriceDistribution(lowerBasePriceRange, upperBasePriceRange);
	spiceBuyCost = static_cast<float>(buyPriceDistribution(engine));

	constexpr auto lowerSellPriceMultiplier = 1.05;
	constexpr auto upperSellPriceMultiplier = 1.5;
	std::uniform_real_distribution<> sellPriceMultiplierDistribution(lowerSellPriceMultiplier, upperSellPriceMultiplier);
	spiceSellCost = spiceBuyCost * static_cast<float>(sellPriceMultiplierDistribution(engine));
}

void Planet::generateCycleInfo(RandomEngine& engine)
{
	constexpr auto lowerCycleBoundary = 2;
	constexpr auto upperCycleBoundary = 5;
	std::uniform_int_distribution<> cycleDistribution(lowerCycleBoundary, upperCycleBoundary);
	refreshPeriod = cycleDistribution(engine);
	cyclesUntilRefresh = refreshPeriod;
}
} // namespace GameMap
