#include <Core/Game.h>
#include <Utility/RandomGenerator.h>

namespace
{
constexpr int firstLayerIdx = 0;

std::weak_ptr<GameMap::SolarSystem> randomizeSolarSystem(GameMap::Galaxy::SystemLayer layer)
{
	constexpr int lowerBound = 0;
	const int upperBound = static_cast<int>(layer.size() - 1);
	auto selectedIdx = utility::RandomGenerator::getInt(lowerBound, upperBound);
	return layer[selectedIdx];
}

std::weak_ptr<GameMap::Planet> randomizeStartingPlanetFromLayer(GameMap::Galaxy::SystemLayer layer)
{
	auto solarSystem = randomizeSolarSystem(layer).lock();
	if (not solarSystem)
	{
		throw std::runtime_error("Selected dead solar system pointer");
	}
	constexpr int lowerBound = 0;
	const int upperBound = static_cast<int>(solarSystem->getPlanetCount() - 1);
	auto selectedIdx = utility::RandomGenerator::getInt(lowerBound, upperBound);
	return (*solarSystem)[selectedIdx];
}

float randomizeStartingSpiceAmount()
{
	constexpr float lowerBound = 60.0f;
	constexpr float upperBound = 100.0f;
	return utility::RandomGenerator::getFloat(lowerBound, upperBound);
}

void performTempAction(GameMap::Galaxy& galaxy)
{
	std::cout << galaxy;
	std::cin.get();
}
} // namespace

namespace core
{
Game::Game(Time::GameTimeService&& providedTimeService)
	: timeService(std::move(providedTimeService))
	, galaxy(GameMap::Galaxy(timeService))
	, player(Entity::Player(randomizeStartingSpiceAmount()))
	, travelAgent(Mechanics::TravelAgent(randomizeStartingPlanetFromLayer(galaxy[firstLayerIdx])))
{
}

bool Game::run()
{
	std::cout << "Current planet data ===========================================\n";
	travelAgent.printCurrentPlanetData();
	std::cin.get();
	performTempAction(galaxy);
	travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::buySpice, 3.0f);
	timeService.update();
	return travelAgent.isEndPlanetReached();
}

void Game::start()
{
	//while (not finished)
	for (int i = 0; i < 10; i++)
	{
		finished = run();
	}
}
} // namespace core
