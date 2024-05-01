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
		interconnectSolarSystems();
	}
}

void Galaxy::interconnectSolarSystems()
{
}
} // namespace GameMap
