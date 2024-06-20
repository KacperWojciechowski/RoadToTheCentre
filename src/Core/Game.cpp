#include <Core/Game.hpp>
#include <Utility/RandomGenerator.hpp>
#include <Action/ActionValidator.hpp>
#include <Action/GeneralActionContext.hpp>
#include <UI/TextInterface.hpp>

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

constexpr float epsilon = 0.05f;

bool isPlayerAbleToBuySpicesOnCurrentPlanet(const Mechanics::TravelAgent& travelAgent, Entity::Player& player)
{
	auto epsilonSpiceCost = travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpiceBuyCost, epsilon);
	auto playerBlixBalance = player.performAction(&Entity::Player::getBlixInStock, Action::EmptyActionParams{});
	return epsilonSpiceCost <= playerBlixBalance;
}

bool isPlayerAbleToTravel(Mechanics::TravelAgent& travelAgent, Entity::Player& player)
{
	auto lowestTravelCost = travelAgent.getCheapestTravelCost();
	auto playerSpiceBalance = player.performAction(&Entity::Player::getSpiceInStock, Action::EmptyActionParams{});
	return lowestTravelCost <= playerSpiceBalance;
}

bool isPlayerOutOfResources(Mechanics::TravelAgent& travelAgent, Entity::Player& player)
{
	return not isPlayerAbleToBuySpicesOnCurrentPlanet(travelAgent, player) and not isPlayerAbleToTravel(travelAgent, player);
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
	if (travelAgent.isEndPlanetReached() or isPlayerOutOfResources(travelAgent, player))
	{
		return true;
	}

	UI::TextInterface::showCurrentState(travelAgent, player);
	UI::TextInterface::showAvailableActions();
	auto actionContext = UI::TextInterface::getNextAction(travelAgent);
	
	if (not Action::Validator::validate(actionContext, travelAgent, player))
	{
		UI::TextInterface::notifyInvalidAction();
		return false;
	}

	travelAgent.performActionOnCurrentPlanet(actionContext.planetActionCallback, actionContext.planetActionParams);
	travelAgent.performActionOnSelf(actionContext.travelAgentActionCallback, actionContext.travelAgentActionParams);
	player.performAction(actionContext.playerActionCallback, actionContext.playerActionParams);
	
	timeService.update();
	return false;
}

void Game::start()
{
	UI::TextInterface::showStartScreen();

	while (not finished)
	{
		finished = run();
	}

	if (isPlayerOutOfResources(travelAgent, player))
	{
		UI::TextInterface::showLoseScreen();
		return;
	}

	if (travelAgent.isEndPlanetReached())
	{
		UI::TextInterface::showWinScreen();
		return;
	}
}
} // namespace core
