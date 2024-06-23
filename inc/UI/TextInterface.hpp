#pragma once

#include <memory>
#include <Action/Action.hpp>

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
		static std::shared_ptr<Action::Action> getNextAction(Action::ExecutingEntities);

		static void showStartScreen();
		static void showWinScreen();
		static void showLoseScreen();

		static void notifyInvalidAction();
	};
}