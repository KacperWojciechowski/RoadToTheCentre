#include <GameMap/Galaxy.h>
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
} // namespace::
Galaxy::Galaxy(Time::GameTimeService& gameTimeService)
{
	auto layersCount = randomizeLayersCount();
	layers.resize(layersCount);
}
} // namespace GameMap
