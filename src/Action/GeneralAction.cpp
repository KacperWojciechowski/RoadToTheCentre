#include <Action/GeneralAction.hpp>
#include <iostream>
#include <Mechanics/TravelAgent.hpp>

namespace Action
{
namespace
{
void exitProgram()
{
	constexpr bool gracefulShutdown = 0;
	std::cout << "Exiting the game\n\n";
	exit(gracefulShutdown);
}
} // namespace::

enum class GeneralAction::Enum : std::size_t
{
	unknown = std::numeric_limits<std::size_t>::max(),
	exit = 0,
	buySpices = 1,
	sellSpices = 2,
	travel = 3,
	wait = 4
};

void GeneralAction::prepareBuySpecificContext(ExecutingEntities executingEntities)
{
	float spiceCount = -1.0f;
	while (spiceCount < 0)
	{
		std::cout << "How many spices would you like to buy (must be >= 0) ?: ";
		std::cin >> spiceCount;
	}
	context = GeneralAction::Context();
	context.planetActionCallback = &GameMap::Planet::buySpice;
	context.playerActionCallback = &Entity::Player::buySpice;
	
	context.planetActionParams = spiceCount;
	auto blixToPay = executingEntities.travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpiceBuyCost, spiceCount);
	context.playerActionParams = TradeActionParams{ .spiceAmount = spiceCount, .blixAmount = blixToPay };
}

void GeneralAction::prepareSellSpecificContext(ExecutingEntities executingEntities)
{
	float spiceCount = -1.0f;
	while (spiceCount < 0)
	{
		std::cout << "How many spices would you like to sell (must be >= 0) ?: ";
		std::cin >> spiceCount;
	}
	context = GeneralAction::Context();
	context.planetActionCallback = &GameMap::Planet::sellSpice;
	context.playerActionCallback = &Entity::Player::sellSpice;

	context.planetActionParams = spiceCount;
	auto blixEarned = executingEntities.travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpiceSellCost, spiceCount);
	context.playerActionParams = TradeActionParams{ .spiceAmount = spiceCount, .blixAmount = blixEarned };
}

void GeneralAction::prepareTravelSpecificContext(ExecutingEntities executingEntities)
{
	ActionIdx planetIdx = 0;
	executingEntities.travelAgent.showTravelOptions();
	while (planetIdx <= 0)
	{
		std::cout << "\n\nRemember that spices serve as fuel for your ship. Where would you like to travel ?: ";
		std::cin >> planetIdx;
	}
	context = GeneralAction::Context();
	context.travelAgentActionCallback = &Mechanics::TravelAgent::travelTo;
	context.playerActionCallback = &Entity::Player::useSpicesForTravel;
	
	context.travelAgentActionParams = planetIdx - 1;
	auto spiceTravelCost = executingEntities.travelAgent.performActionOnSelf(
		&Mechanics::TravelAgent::getTravelCost, context.travelAgentActionParams);
	context.playerActionParams = TravelActionParams{ .spiceAmount = spiceTravelCost };
}

GeneralAction::Enum GeneralAction::actionIdxToEnum(std::size_t actionIdx)
{
	switch (actionIdx)
	{
	case 0: return Enum::exit;
	case 1: return Enum::buySpices;
	case 2: return Enum::sellSpices;
	case 3: return Enum::travel;
	case 4: return Enum::wait;
	default: return Enum::unknown;
	}
}

void GeneralAction::prepareWaitSpecificContext()
{
	context = GeneralAction::Context();
	context.isWaitAction = true;
}

const Action::Context& GeneralAction::getContext() const
{
	return context;
}

void GeneralAction::prepareActionSpecificContext(std::size_t action, ExecutingEntities executingEntities)
{
	auto actionEnum = actionIdxToEnum(action);
	switch (actionEnum)
	{
	case GeneralAction::Enum::exit:
		exitProgram();
		break;
	case GeneralAction::Enum::buySpices:
		prepareBuySpecificContext(executingEntities);
		break;
	case GeneralAction::Enum::sellSpices:
		prepareSellSpecificContext(executingEntities);
		break;
	case GeneralAction::Enum::travel:
		prepareTravelSpecificContext(executingEntities);
		break;
	case GeneralAction::Enum::wait:
		prepareWaitSpecificContext();
		break;
	default:
		break;
	}
}

std::size_t GeneralAction::getActionCount()
{
	constexpr std::size_t actionCount = 4;
	return actionCount;
}

void GeneralAction::execute(ExecutingEntities executingEntities)
{
	executingEntities.player.performAction(context.playerActionCallback, context.playerActionParams);
	executingEntities.travelAgent.performActionOnCurrentPlanet(context.planetActionCallback, context.planetActionParams);
	executingEntities.travelAgent.performActionOnSelf(context.travelAgentActionCallback, context.travelAgentActionParams);
}
} // namespace Action