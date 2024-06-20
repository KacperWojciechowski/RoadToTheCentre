#pragma once
#include <Action/GeneralActionContext.hpp>

namespace UI
{
	class TextInterface
	{
	public:
		static void showCurrentState(const Mechanics::TravelAgent&, Entity::Player&);
		static void showAvailableActions();
		static Action::GeneralActionContext getNextAction(Mechanics::TravelAgent&);

		static void showStartScreen();
		static void showWinScreen();
		static void showLoseScreen();

		static void notifyInvalidAction();
	};
}