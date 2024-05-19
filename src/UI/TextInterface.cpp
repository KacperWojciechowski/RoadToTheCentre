#include <UI/TextInterface.h>
#include <iostream>
#include <GameMap/Planet.h>
#include <Entities/Player.h>


namespace
{
constexpr std::size_t actionCount = 4;

void scroll()
{
	std::cout << "\n\n\n\n\n\n\n\n\n\n";
}

enum class ActionEnum
{
	unknown = 0,
	buySpices = 1,
	sellSpices = 2,
	travel = 3,
	wait = 4
};

ActionEnum actionIdxToEnum(std::size_t actionIdx)
{
	switch (actionIdx)
	{
	case 1: return ActionEnum::buySpices;
	case 2: return ActionEnum::sellSpices;
	case 3: return ActionEnum::travel;
	case 4: return ActionEnum::wait;
	default: return ActionEnum::unknown;
	}
}

Action::ActionContext getBuySpecificContext(const Mechanics::TravelAgent& travelAgent)
{
	float spiceCount = -1.0f;
	while (spiceCount < 0)
	{
		std::cout << "How many spices would you like to buy (must be >= 0) ?: ";
		std::cin >> spiceCount;
	}
	Action::ActionContext context;
	context.planetActionCallback = &GameMap::Planet::buySpice;
	context.playerActionCallback = &Entity::Player::buySpice;
	
	context.planetActionContext = spiceCount;
	auto blixToPay = travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpiceBuyCost, spiceCount);
	context.playerActionContext = Action::PlayerTradeActionContext{ .spiceAmount = spiceCount, .blixAmount = blixToPay };

	return context;
}

Action::ActionContext getSellSpecificContext(const Mechanics::TravelAgent& travelAgent)
{
	float spiceCount = -1.0f;
	while (spiceCount < 0)
	{
		std::cout << "How many spices would you like to sell (must be >= 0) ?: ";
		std::cin >> spiceCount;
	}
	Action::ActionContext context;
	context.planetActionCallback = &GameMap::Planet::sellSpice;
	context.playerActionCallback = &Entity::Player::sellSpice;

	context.planetActionContext = spiceCount;
	auto blixEarned = travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpiceSellCost, spiceCount);
	context.playerActionContext = Action::PlayerTradeActionContext{ .spiceAmount = spiceCount, .blixAmount = blixEarned };

	return context;
}

Action::ActionContext getTravelSpecificContext(Mechanics::TravelAgent& travelAgent)
{
	std::size_t planetIdx = 0;
	travelAgent.showTravelOptions();
	while (planetIdx <= 0)
	{
		std::cout << "\n\nRemember that spices serve as fuel for your ship. Where would you like to travel ?: ";
		std::cin >> planetIdx;
	}
	Action::ActionContext context;
	context.travelAgentActionCallback = &Mechanics::TravelAgent::travelTo;
	context.playerActionCallback = &Entity::Player::useSpicesForTravel;
	
	context.travelAgentActionContext = planetIdx - 1;
	auto spiceTravelCost = travelAgent.performActionOnSelf(&Mechanics::TravelAgent::getTravelCost, context.travelAgentActionContext);
	context.playerActionContext = Action::PlayerTravelActionContext{ .spiceAmount = spiceTravelCost };

	return context;
}

Action::ActionContext getWaitSpecificContext()
{
	std::cout << "You rest on the current planet for the next cycle\n\n";
	Action::ActionContext context;
	context.isWaitAction = true;
	return context;
}

Action::ActionContext getActionSpecificContext(ActionEnum action, Mechanics::TravelAgent& travelAgent)
{
	switch (action)
	{
	case ActionEnum::buySpices:
		return getBuySpecificContext(travelAgent);
	case ActionEnum::sellSpices:
		return getSellSpecificContext(travelAgent);
	case ActionEnum::travel:
		return getTravelSpecificContext(travelAgent);
	case ActionEnum::wait:
		return getWaitSpecificContext();
	default:
		return {};
	}
}
} // namespace::

namespace UI
{
void TextInterface::showCurrentState(const Mechanics::TravelAgent& travelAgent, Entity::Player& player)
{
	std::cout << "Current planet data ===========================================\n";
	std::cout << travelAgent;
	std::cout << "Player data ===================================================\n";
	std::cout << player;
}
	
void TextInterface::showAvailableActions()
{
	std::cout << "\n\n"
		"Available actions:\n"
		"1. Buy spices\n"
		"2. Sell spices\n"
		"3. Travel\n"
		"4. Wait\n\n";
}

Action::ActionContext TextInterface::getNextAction(Mechanics::TravelAgent& travelAgent)
{
	std::size_t actionIdx = 0u;
	while (actionIdx <= 0 or actionIdx > actionCount)
	{
		std::cout << "Your choice ?: ";
		std::cin >> actionIdx;
	}
	auto action = actionIdxToEnum(actionIdx);
	return getActionSpecificContext(action, travelAgent);
}
	
void TextInterface::showStartScreen()
{
	std::cout << "You're a spice merchant. After a fairly successful career on your home planet\n"
		"You decided it is time to try broadening your horizons and traveling to other planets.\n"
		"After buying a ship, you gathered your money and wares, and started your journey, with the\n"
		"goal to get to the galaxy center.";
	std::cin.get();
	scroll();
}

void TextInterface::showWinScreen()
{
	scroll();
	std::cout << "After extensive travels, you finally reached your goal - the galaxy center.\n"
		"With all the possible future profits in mind, you cannot wait to get to more work.\n\n"
		"Well done - you've completed the game.";
	std::cin.get();
	scroll();
}
void TextInterface::showLoseScreen()
{
	scroll();
	std::cout << "The fortune didn't smile at you, and after lenghty travels, you did not achieve profit.\n"
		"With the last resources you had, you returned to your home planet to start again.\n\n"
		"You lost the game - restart the program to try again.";
	std::cin.get();
	scroll();
}

void TextInterface::notifyInvalidAction()
{
	std::cout << "\n\nThis action contains invalid parameters. Please try again.\n\n";
}
} // namespace UI
