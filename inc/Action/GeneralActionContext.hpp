#pragma once

#include <Mechanics/TravelAgent.hpp>
#include <Entities/Player.hpp>

namespace GameMap
{
class Planet;
} // namespace GameMap

namespace Action
{
struct EmptyActionParams
{
};

struct TradeActionParams
{
	float spiceAmount;
	float blixAmount;
};

struct TravelActionParams
{
	float spiceAmount;
};

struct GeneralActionContext
{
	GeneralActionContext()
		: planetActionCallback(nullptr)
		, playerActionCallback(nullptr)
		, travelAgentActionCallback(nullptr)
		, playerActionParams(EmptyActionParams{})
		, planetActionParams(0.0f)
		, travelAgentActionParams(0u)
		, isWaitAction(false)
	{}

	Mechanics::TravelAgent::PlanetActionCallback planetActionCallback;
	Entity::Player::PlayerActionCallback playerActionCallback;
	Mechanics::TravelAgent::TravelAgentActionCallback travelAgentActionCallback;
	
	PlayerActionParams playerActionParams;
	float planetActionParams;
	std::size_t travelAgentActionParams;
	
	bool isWaitAction = false;
};
} // namespace Action
