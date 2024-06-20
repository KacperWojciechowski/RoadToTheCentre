#include <Action/GeneralAction.hpp>
#include <iostream>
#include <Action/GeneralActionContext.hpp>
#include <Mechanics/TravelAgent.hpp>

namespace Action
{
enum class GeneralActionEnum : std::size_t
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
GeneralActionContext getBuySpecificContext(const Mechanics::TravelAgent& travelAgent)
{
	float spiceCount = -1.0f;
	while (spiceCount < 0)
	{
		std::cout << "How many spices would you like to buy (must be >= 0) ?: ";
		std::cin >> spiceCount;
	}
	GeneralActionContext context;
	context.planetActionCallback = &GameMap::Planet::buySpice;
	context.playerActionCallback = &Entity::Player::buySpice;
	
	context.planetActionContext = spiceCount;
	auto blixToPay = travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpiceBuyCost, spiceCount);
	context.playerActionContext = PlayerTradeActionContext{ .spiceAmount = spiceCount, .blixAmount = blixToPay };

	return context;
}

GeneralActionContext getSellSpecificContext(const Mechanics::TravelAgent& travelAgent)
{
	float spiceCount = -1.0f;
	while (spiceCount < 0)
	{
		std::cout << "How many spices would you like to sell (must be >= 0) ?: ";
		std::cin >> spiceCount;
	}
	GeneralActionContext context;
	context.planetActionCallback = &GameMap::Planet::sellSpice;
	context.playerActionCallback = &Entity::Player::sellSpice;

	context.planetActionContext = spiceCount;
	auto blixEarned = travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpiceSellCost, spiceCount);
	context.playerActionContext = PlayerTradeActionContext{ .spiceAmount = spiceCount, .blixAmount = blixEarned };

	return context;
}

GeneralActionContext getTravelSpecificContext(Mechanics::TravelAgent& travelAgent)
{
	std::size_t planetIdx = 0;
	travelAgent.showTravelOptions();
	while (planetIdx <= 0)
	{
		std::cout << "\n\nRemember that spices serve as fuel for your ship. Where would you like to travel ?: ";
		std::cin >> planetIdx;
	}
	GeneralActionContext context;
	context.travelAgentActionCallback = &Mechanics::TravelAgent::travelTo;
	context.playerActionCallback = &Entity::Player::useSpicesForTravel;
	
	context.travelAgentActionContext = planetIdx - 1;
	auto spiceTravelCost = travelAgent.performActionOnSelf(&Mechanics::TravelAgent::getTravelCost, context.travelAgentActionContext);
	context.playerActionContext = PlayerTravelActionContext{ .spiceAmount = spiceTravelCost };

	return context;
}

GeneralActionContext getWaitSpecificContext()
{
	std::cout << "You rest on the current planet for the next cycle\n\n";
	GeneralActionContext context;
	context.isWaitAction = true;
	return context;
}

GeneralActionContext getExitContext()
{
	std::cout << "Exiting the game\n\n";
	GeneralActionContext context;
	//context.isExitAction = true;
	return context;
}
} // namespace::

GeneralActionEnum actionIdxToEnum(std::size_t actionIdx)
{
	switch (actionIdx)
	{
	case 0: return GeneralActionEnum::exit;
	case 1: return GeneralActionEnum::buySpices;
	case 2: return GeneralActionEnum::sellSpices;
	case 3: return GeneralActionEnum::travel;
	case 4: return GeneralActionEnum::wait;
	default: return GeneralActionEnum::unknown;
	}
}

GeneralActionContext getActionSpecificContext(GeneralActionEnum action, Mechanics::TravelAgent& travelAgent)
{
	switch (action)
	{
	case GeneralActionEnum::exit:
		return getExitContext();
	case GeneralActionEnum::buySpices:
		return getBuySpecificContext(travelAgent);
	case GeneralActionEnum::sellSpices:
		return getSellSpecificContext(travelAgent);
	case GeneralActionEnum::travel:
		return getTravelSpecificContext(travelAgent);
	case GeneralActionEnum::wait:
		return getWaitSpecificContext();
	default:
		return {};
	}
}
} // namespace Action