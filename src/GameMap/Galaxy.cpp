#include <GameMap/Galaxy.h>
#include <GameMap/SolarSystem.h>
#include <Utility/RandomGenerator.h>

namespace GameMap
{
namespace
{
std::size_t randomizeLayersCount()
{
	constexpr auto lowerBound = 3;
	constexpr auto upperBound = 10;
	return static_cast<std::size_t>(utility::RandomGenerator::getInt(lowerBound, upperBound));
}

std::size_t randomizeSolarSystemsCount()
{
	constexpr auto lowerBound = 1;
	constexpr auto upperBound = 4;
	return static_cast<std::size_t>(utility::RandomGenerator::getInt(lowerBound, upperBound));
}

float randomizeInterstelarTravelCost()
{
	constexpr auto lowerBound = 10.0f;
	constexpr auto upperBound = 30.0f;
	return utility::RandomGenerator::getFloat(lowerBound, upperBound);
}

void connectSolarSystemsHierarchy(std::vector<Galaxy::SystemLayer>& layers, float interstelarTravelCost)
{
	constexpr int offset = 1;
	for (auto layer = layers.begin(); std::next(layer, offset) != layers.end(); layer++)
	{
		for (auto system : *layer)
		{
			auto adjLayer = std::next(layer, offset);
			for (auto adjSystem : *adjLayer)
			{
				if (system and adjSystem)
				{
					system->linkSolarSystems(adjSystem, interstelarTravelCost);
				}
			}
		}
	}
}
} // namespace::

Galaxy::Galaxy(Time::GameTimeService& gameTimeService)
{
	auto layersCount = randomizeLayersCount();
	layers.resize(layersCount);

	for (auto layer : layers)
	{
		auto solarSystemsCount = randomizeSolarSystemsCount();
		for (std::size_t i = 0; i < solarSystemsCount; i++)
		{
			layer.emplace_back(std::move(SolarSystem::create(gameTimeService)));
		}
	}
	connectSolarSystemsHierarchy(layers, randomizeInterstelarTravelCost());
}
} // namespace GameMap
