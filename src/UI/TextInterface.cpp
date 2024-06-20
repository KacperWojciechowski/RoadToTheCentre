#include <UI/TextInterface.hpp>
#include <iostream>
#include <GameMap/Planet.hpp>
#include <Entities/Player.hpp>
#include <limits>
#include <Action/GeneralAction.hpp>

namespace
{
void scroll()
{
	std::cout << "\n\n\n\n\n\n\n\n\n\n";
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
		"4. Wait\n\n"
		"0. Exit\n\n";
}

std::shared_ptr<Action::ActionContext> TextInterface::getNextAction(Mechanics::TravelAgent& travelAgent)
{
	std::size_t actionIdx = std::numeric_limits<std::size_t>::max();
	auto action = std::make_shared<Action::GeneralAction>();
	while (actionIdx > action->getActionCount())
	{
		std::cout << "Your choice ?: ";
		std::cin >> actionIdx;
	}
	return action->getActionSpecificContext(actionIdx, travelAgent);
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
