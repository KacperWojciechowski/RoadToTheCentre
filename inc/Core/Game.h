#pragma once

#include <Mechanics/TravelAgent.h>
#include <Services/GameTimeService.h>
#include <Entities/Player.h>
#include <GameMap/Galaxy.h>

namespace core
{
class Game
{
public:
	Game(Time::GameTimeService&&);
	void start();
private:
	bool run();

	Time::GameTimeService timeService;
	GameMap::Galaxy galaxy;
	Entity::Player player;
	Mechanics::TravelAgent travelAgent;

	bool finished = false;
};
} // namespace core
