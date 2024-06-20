#include <Action/ActionValidator.hpp>
#include <Mechanics/TravelAgent.hpp>
#include <Entities/Player.hpp>
#include <GameMap/Planet.hpp>

namespace
{
bool isSellAction(const Action::GeneralActionContext& context)
{
	return context.planetActionCallback == &GameMap::Planet::sellSpice and context.playerActionCallback == &Entity::Player::sellSpice;
}

bool isBuyAction(const Action::GeneralActionContext& context)
{
	return context.planetActionCallback == &GameMap::Planet::buySpice and context.playerActionCallback == &Entity::Player::buySpice;
}

bool isTravelAction(const Action::GeneralActionContext& context)
{
	return context.playerActionCallback == &Entity::Player::useSpicesForTravel and context.travelAgentActionCallback == &Mechanics::TravelAgent::travelTo;
}

bool isWaitAction(const Action::GeneralActionContext& context)
{
	return context.isWaitAction;
}

constexpr float dummyPlanetContext = 0.0f;

bool validateTradeAction(const Action::GeneralActionContext& context, Mechanics::TravelAgent& travelAgent, Entity::Player& player) 
{
	if (not std::holds_alternative<Action::PlayerTradeActionContext>(context.playerActionContext))
	{
		return false;
	}

	auto spicesInStock = player.performAction(&Entity::Player::getSpiceInStock, Action::EmptyActionContext{});
	auto blixInStock = player.performAction(&Entity::Player::getBlixInStock, Action::EmptyActionContext{});

	auto planetSpicesInStock = travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpicesInStock, dummyPlanetContext);
	auto& playerActionContext = std::get<Action::PlayerTradeActionContext>(context.playerActionContext);
		
	if (isSellAction(context))
	{
		return spicesInStock >= context.planetActionContext
			and spicesInStock >= playerActionContext.spiceAmount;
	}

	if (isBuyAction(context))
	{
		return planetSpicesInStock >= context.planetActionContext
			and planetSpicesInStock >= playerActionContext.spiceAmount
			and blixInStock >= playerActionContext.blixAmount;
	}
	return false;
}

bool validateTravelAction(const Action::GeneralActionContext& context, Mechanics::TravelAgent& travelAgent, Entity::Player& player)
{
	if (not std::holds_alternative<Action::PlayerTravelActionContext>(context.playerActionContext))
	{
		return false;
	}

	auto spicesInStock = player.performAction(&Entity::Player::getSpiceInStock, Action::EmptyActionContext{});
	auto& playerActionContext = std::get<Action::PlayerTravelActionContext>(context.playerActionContext);

	auto adjPlanetsCount = travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getAdjacentPlanetCount, dummyPlanetContext);

	return spicesInStock >= playerActionContext.spiceAmount
		and context.travelAgentActionContext < adjPlanetsCount;
}
} // namespace

namespace Action
{
	bool Validator::validate(const GeneralActionContext& context, Mechanics::TravelAgent& travelAgent, Entity::Player& player)
	{	
		if (isSellAction(context) or isBuyAction(context))
		{
			return validateTradeAction(context, travelAgent, player);
		}
		if (isTravelAction(context))
		{
			return validateTravelAction(context, travelAgent, player);
		}
		if (isWaitAction(context))
		{
			return true;
		}
		return false;
	}
} // namespace Action
