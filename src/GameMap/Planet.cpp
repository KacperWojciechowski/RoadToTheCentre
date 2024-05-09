#include <GameMap/Planet.h>
#include <Utility/RandomGenerator.h>
#include <cassert>
#include <algorithm>
#include <Utility/EnumSerializer.h>

namespace GameMap
{
namespace
{
int generatePlanetId()
{
	constexpr auto lowerBound = 0x01000000;
	constexpr auto upperBound = 0x0FFFFFFF;
	return utility::RandomGenerator::getInt(lowerBound, upperBound);
}

float generateSpiceCapacityInfo()
{
	constexpr auto lowerBound = 10.0f;
	constexpr auto upperBound = 50.0f;
	return utility::RandomGenerator::getFloat(lowerBound, upperBound);
}

float generateSellPrice(float buyPrice)
{
	constexpr auto lowerSellMultiplierBound = 1.05f;
	constexpr auto upperSellMultiplierBound = 1.5f;

	return buyPrice * utility::RandomGenerator::getFloat(lowerSellMultiplierBound, upperSellMultiplierBound);
}

float generateBuyPrice()
{
	constexpr auto lowerBasePriceBound = 50.0f;
	constexpr auto upperBasePriceBound = 300.0f;
	return utility::RandomGenerator::getFloat(lowerBasePriceBound, upperBasePriceBound);
}

int generateCycleRefreshPeriod()
{
	constexpr auto lowerBound = 2;
	constexpr auto upperBound = 5;
	return utility::RandomGenerator::getInt(lowerBound, upperBound);
}
} // namespace::

std::ostream& operator<<(std::ostream& out, const Planet& planet)
{
	out << "[" << std::hex << planet.starId << "-" << planet.planetId << std::dec << "] {\n";
	out << "\tspices stock = " << planet.spiceInStock << "/" << planet.spiceCapacity << " tons\n";
	out << "\tpricing [buy/sell] = " << planet.spiceBuyCost << "/" << planet.spiceSellCost << " blix\n";
	out << "\ttime until refresh = " << planet.cyclesUntilRefresh << "\n}\n";
	return out; 
}

Planet::Planet(int starId, CreationGuard) 
	: starId {starId}
	, planetId {generatePlanetId()}
	, spiceCapacity {generateSpiceCapacityInfo()}
	, spiceBuyCost {generateBuyPrice()}
	, spiceSellCost {generateSellPrice(spiceBuyCost)}
	, refreshPeriod {generateCycleRefreshPeriod()}
	, spiceInStock {spiceCapacity}
	, cyclesUntilRefresh {refreshPeriod}
{
}

PlanetPtr Planet::create(int starId, Time::GameTimeService& gameTimeService)
{
	auto planet = std::make_shared<Planet>(starId, CreationGuard{});
	gameTimeService.subscribe(planet);

	return planet;
}

bool Planet::operator==(const Planet& other) const
{
	return (starId == other.starId
		and planetId == other.planetId
		and spiceCapacity == other.spiceCapacity
		and spiceBuyCost == other.spiceBuyCost
		and spiceSellCost == other.spiceSellCost
		and refreshPeriod == other.refreshPeriod);
}

bool Planet::operator!=(const Planet& other) const
{
	return not ((*this) == other);
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

void Planet::connectIntraSystemPlanet(std::weak_ptr<Planet> planet, float travelCost)
{
	addAdjacentPlanet(planet, AdjacencyType::intraSystem, travelCost);
}

void Planet::connectInterStelarPlanet(std::weak_ptr<Planet> planet, float travelCost)
{
	addAdjacentPlanet(planet, AdjacencyType::interStelar, travelCost);
}

void Planet::addAdjacentPlanet(std::weak_ptr<Planet> planet, AdjacencyType adjType, float travelCost)
{
	auto tgtPlanet = planet.lock();
	
	auto planetChecker = [&tgtPlanet](AdjacencyInfo& checkedPlanet) {
		return checkedPlanet.adjPlanet.lock() == tgtPlanet;
	};
	auto isMarkedAsAdjacent = adjacentPlanets.end() != std::ranges::find_if(adjacentPlanets, planetChecker);
	
	if (tgtPlanet and isMarkedAsAdjacent and (*tgtPlanet) != (*this))
	{
		adjacentPlanets.emplace_back(planet, adjType, travelCost);
		tgtPlanet->addAdjacentPlanet(shared_from_this(), adjType, travelCost);
	}
}

float Planet::getSpiceSellCost() const
{
	return spiceSellCost;
}

float Planet::getSpiceBuyCost() const
{
	return spiceBuyCost;
}

float Planet::buySpice(float amount)
{
	assert(amount <= spiceInStock);

	spiceInStock -= amount;

	return amount * spiceBuyCost;
}

float Planet::sellSpice(float amount)
{
	return amount * spiceSellCost;
}

void Planet::printAdjacencyPlanetsInfo(std::ostream& out)
{
	int planetIdx = 1;
	out << "== Adjacency planets: ==\n";
	for (auto& adjInfo : adjacentPlanets)
	{
		auto planetPtr = adjInfo.adjPlanet.lock();
		if (planetPtr)
		{
			out << planetIdx << ". " << planetPtr;
			out << "Travel type: " 
				<< utility::EnumSerializer<AdjacencyType>(adjInfo.adjType)() 
				<< ", travel cost: " 
				<< adjInfo.travelCost 
				<< "\n----\n";
		}
		planetIdx++;
	}
}

void Planet::setAsEndPlanet()
{
	endPlanet = true;
}

bool Planet::isEndPlanet()
{
	return endPlanet;
}
Planet::AdjacencyInfo Planet::getAdjacentPlanetInfo(std::size_t idx)
{
	if (idx >= adjacentPlanets.size())
	{
		return {};
	}
	if (not adjacentPlanets.at(idx).adjPlanet.lock())
	{
		return {};
	}
	return adjacentPlanets.at(idx);
}
} // namespace GameMap
