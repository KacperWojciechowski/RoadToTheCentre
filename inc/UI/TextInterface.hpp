#pragma once

#include <memory>

namespace Mechanics
{
class TravelAgent;
} // namespace Mechanics

namespace Entity
{
class Player;
} // namespace Entity

namespace Action
{
class ActionContext;
} // namespace Action

namespace UI
{
	class TextInterface
	{
	public:
		static void showCurrentState(const Mechanics::TravelAgent&, Entity::Player&);
		static void showAvailableActions();
		static std::shared_ptr<Action::ActionContext> getNextAction(Mechanics::TravelAgent&);

		static void showStartScreen();
		static void showWinScreen();
		static void showLoseScreen();

		static void notifyInvalidAction();
	};
}