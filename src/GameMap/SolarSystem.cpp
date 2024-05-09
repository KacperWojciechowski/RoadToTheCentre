#include <GameMap/SolarSystem.h>
#include <Utility/RandomGenerator.h>

namespace GameMap
{
namespace
{
int randomizePlanetCount()
{
	constexpr auto lowerBound = 1;
	constexpr auto upperBound = 5;
	return utility::RandomGenerator::getInt(lowerBound, upperBound);
}

int randomizeStarId()
{
	constexpr auto lowerBound = 0x01000000;
	constexpr auto upperBound = 0x0FFFFFFF;
	return utility::RandomGenerator::getInt(lowerBound, upperBound);
}

float randomizeTravelCost()
{
	constexpr auto lowerBound = 0.3f;
	constexpr auto upperBound = 1.0f;
	return utility::RandomGenerator::getFloat(lowerBound, upperBound);
}
} // namespace

std::shared_ptr<SolarSystem> SolarSystem::create(Time::GameTimeService& gameTimeService)
{
	auto planetCount = randomizePlanetCount();
	auto starId = randomizeStarId();

	std::vector<PlanetPtr> planetsContainer;
	planetsContainer.reserve(planetCount);

	for (int i = 0; i < planetCount; i++)
	{
		planetsContainer.emplace_back(std::move(Planet::create(starId, gameTimeService)));
	}

	return std::make_shared<SolarSystem>(std::move(planetsContainer), CreationGuard{});
}
	
SolarSystem::SolarSystem(std::vector<PlanetPtr>&& planetsContainer, CreationGuard) 
	: planets(std::move(planetsContainer))
{
	interconnectPlanets(randomizeTravelCost());
}

SolarSystem::const_iterator SolarSystem::begin()
{
	return planets.cbegin();
}

SolarSystem::const_iterator SolarSystem::end()
{
	return planets.cend();
}

PlanetPtr SolarSystem::operator[](int planetIndex)
{
	return planets.at(planetIndex);
}

std::size_t SolarSystem::getPlanetCount() const
{
	return planets.size();
}

void SolarSystem::linkSolarSystems(std::weak_ptr<SolarSystem> solarSystem, float travelCost)
{
	auto system = solarSystem.lock();
	for (auto adjPlanet = system->begin(); adjPlanet != system->end(); adjPlanet++)
	{
		for (auto ownPlanet = begin(); ownPlanet != end(); ownPlanet++)
		{
			(*ownPlanet)->connectInterStelarPlanet(*adjPlanet, travelCost);
		}
	}
}

void SolarSystem::interconnectPlanets(float travelCost)
{
	for (auto currentPlanet = planets.begin(); currentPlanet != planets.end(); currentPlanet++)
	{
		for (auto nextPlanet = std::next(currentPlanet, 1); nextPlanet != planets.end(); nextPlanet++)
		{
			if (*currentPlanet and *nextPlanet)
			{
				(*currentPlanet)->connectIntraSystemPlanet(*nextPlanet, travelCost);
			}
		}
	}
}

std::ostream& operator<<(std::ostream& out, const SolarSystem& solarSystem)
{
	out << "[SolarSystem] { -----------------------------------------------\n";
	for (auto planet = solarSystem.planets.cbegin(); planet != solarSystem.planets.cend(); planet++)
	{
		out << **planet;
	}
	out << "}\n";
	return out;
}
} // namespace GameMap
