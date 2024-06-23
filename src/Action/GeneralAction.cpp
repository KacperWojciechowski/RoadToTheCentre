#include <Action/GeneralAction.hpp>
#include <iostream>
#include <Mechanics/TravelAgent.hpp>

namespace Action
{
enum class GeneralAction::Enum : std::size_t
{
	unknown = std::numeric_limits<std::size_t>::max(),
	exit = 0,
	buySpices = 1,
	sellSpices = 2,
	travel = 3,
	wait = 4
};

namespace
{
std::shared_ptr<ActionContext> getBuySpecificContext(ExecutingEntities executingEntities)
{
	float spiceCount = -1.0f;
	while (spiceCount < 0)
	{
		std::cout << "How many spices would you like to buy (must be >= 0) ?: ";
		std::cin >> spiceCount;
	}
	auto context = std::make_shared<GeneralAction::Context>();
	context->planetActionCallback = &GameMap::Planet::buySpice;
	context->playerActionCallback = &Entity::Player::buySpice;
	
	context->planetActionParams = spiceCount;
	auto blixToPay = executingEntities.travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpiceBuyCost, spiceCount);
	context->playerActionParams = TradeActionParams{ .spiceAmount = spiceCount, .blixAmount = blixToPay };

	return context;
}

std::shared_ptr<ActionContext> getSellSpecificContext(const Mechanics::TravelAgent& travelAgent)
{
	float spiceCount = -1.0f;
	while (spiceCount < 0)
	{
		std::cout << "How many spices would you like to sell (must be >= 0) ?: ";
		std::cin >> spiceCount;
	}
	auto context = std::make_shared<GeneralAction::Context>();
	context->planetActionCallback = &GameMap::Planet::sellSpice;
	context->playerActionCallback = &Entity::Player::sellSpice;

	context->planetActionParams = spiceCount;
	auto blixEarned = travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpiceSellCost, spiceCount);
	context->playerActionParams = TradeActionParams{ .spiceAmount = spiceCount, .blixAmount = blixEarned };

	return context;
}

std::shared_ptr<ActionContext> getTravelSpecificContext(Mechanics::TravelAgent& travelAgent)
{
	std::size_t planetIdx = 0;
	travelAgent.showTravelOptions();
	while (planetIdx <= 0)
	{
		std::cout << "\n\nRemember that spices serve as fuel for your ship. Where would you like to travel ?: ";
		std::cin >> planetIdx;
	}
	auto context = std::make_shared<GeneralAction::Context>();
	context->travelAgentActionCallback = &Mechanics::TravelAgent::travelTo;
	context->playerActionCallback = &Entity::Player::useSpicesForTravel;
	
	context->travelAgentActionParams = planetIdx - 1;
	auto spiceTravelCost = travelAgent.performActionOnSelf(&Mechanics::TravelAgent::getTravelCost, context->travelAgentActionParams);
	context->playerActionParams = TravelActionParams{ .spiceAmount = spiceTravelCost };

	return context;
}

std::shared_ptr<ActionContext> getWaitSpecificContext()
{
	std::cout << "You rest on the current planet for the next cycle\n\n";
	auto context = std::make_shared<GeneralAction::Context>();
	context->isWaitAction = true;
	return context;
}

void getExitContext()
{
	constexpr bool gracefulShutdown = 0;
	std::cout << "Exiting the game\n\n";
	exit(gracefulShutdown);
}

GeneralAction::Enum actionIdxToEnum(std::size_t actionIdx)
{
	switch (actionIdx)
	{
	case 0: return GeneralAction::Enum::exit;
	case 1: return GeneralAction::Enum::buySpices;
	case 2: return GeneralAction::Enum::sellSpices;
	case 3: return GeneralAction::Enum::travel;
	case 4: return GeneralAction::Enum::wait;
	default: return GeneralAction::Enum::unknown;
	}
}
} // namespace::

std::shared_ptr<ActionContext> GeneralAction::getActionSpecificContext(std::size_t action, ExecutingEntities executingEntities)
{
	auto actionEnum = actionIdxToEnum(action);
	switch (actionEnum)
	{
	case GeneralAction::Enum::exit:
		getExitContext();
		return nullptr;
	case GeneralAction::Enum::buySpices:
		return getBuySpecificContext(executingEntities);
	case GeneralAction::Enum::sellSpices:
		return getSellSpecificContext(executingEntities);
	case GeneralAction::Enum::travel:
		return getTravelSpecificContext(executingEntities);
	case GeneralAction::Enum::wait:
		return getWaitSpecificContext();
	default:
		return nullptr;
	}
}

std::size_t GeneralAction::getActionCount()
{
	constexpr std::size_t actionCount = 4;
	return actionCount;
}
} // namespace Action