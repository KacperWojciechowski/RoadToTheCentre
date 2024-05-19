#pragma once

#include <Mechanics/TravelAgent.h>
#include <Entities/Player.h>
#include <GameMap/Planet.h>

namespace Action
{
struct ActionContext
{
	ActionContext()
		: planetActionCallback(nullptr)
		, playerActionCallback(nullptr)
		, travelAgentActionCallback(nullptr)
		, playerActionContext(Action::EmptyActionContext{})
		, planetActionContext(0.0f)
		, travelAgentActionContext(0u)
		, isWaitAction(false)
	{}

	Mechanics::TravelAgent::PlanetActionCallback planetActionCallback;
	Entity::Player::PlayerActionCallback playerActionCallback;
	Mechanics::TravelAgent::TravelAgentActionCallback travelAgentActionCallback;
	PlayerActionContext playerActionContext;
	float planetActionContext;
	std::size_t travelAgentActionContext;
	bool isWaitAction = false;
};
} // namespace Action
