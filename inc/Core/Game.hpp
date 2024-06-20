#pragma once

#include <Mechanics/TravelAgent.hpp>
#include <Services/GameTimeService.hpp>
#include <Entities/Player.hpp>
#include <GameMap/Galaxy.hpp>

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
