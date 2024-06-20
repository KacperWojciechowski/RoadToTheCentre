#include <Action/ActionValidator.hpp>
#include <Mechanics/TravelAgent.hpp>
#include <Entities/Player.hpp>
#include <GameMap/Planet.hpp>

namespace
{
constexpr float dummyPlanetParams = 0.0f;

bool isSellAction(const Action::GeneralActionContext& context)
{
	return context.planetActionCallback == &GameMap::Planet::sellSpice and 
		   context.playerActionCallback == &Entity::Player::sellSpice;
}

bool isBuyAction(const Action::GeneralActionContext& context)
{
	return context.planetActionCallback == &GameMap::Planet::buySpice and 
		   context.playerActionCallback == &Entity::Player::buySpice;
}

bool isTravelAction(const Action::GeneralActionContext& context)
{
	return context.playerActionCallback == &Entity::Player::useSpicesForTravel and 
		   context.travelAgentActionCallback == &Mechanics::TravelAgent::travelTo;
}

bool isWaitAction(const Action::GeneralActionContext& context)
{
	return context.isWaitAction;
}

bool validateTradeAction(
	const Action::GeneralActionContext& context, 
	Mechanics::TravelAgent& travelAgent, 
	Entity::Player& player) 
{
	if (not std::holds_alternative<Action::TradeActionParams>(context.playerActionParams))
	{
		return false;
	}

	auto spicesInStock = player.performAction(&Entity::Player::getSpiceInStock, Action::EmptyActionParams{});
	auto blixInStock = player.performAction(&Entity::Player::getBlixInStock, Action::EmptyActionParams{});

	auto planetSpicesInStock = travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpicesInStock, dummyPlanetParams);
	auto& playerActionParams = std::get<Action::TradeActionParams>(context.playerActionParams);
		
	if (isSellAction(context))
	{
		return spicesInStock >= context.planetActionParams
			and spicesInStock >= playerActionParams.spiceAmount;
	}

	if (isBuyAction(context))
	{
		return planetSpicesInStock >= context.planetActionParams
			and planetSpicesInStock >= playerActionParams.spiceAmount
			and blixInStock >= playerActionParams.blixAmount;
	}
	return false;
}

bool validateTravelAction(const Action::GeneralActionContext& context, Mechanics::TravelAgent& travelAgent, Entity::Player& player)
{
	if (not std::holds_alternative<Action::TravelActionParams>(context.playerActionParams))
	{
		return false;
	}

	auto spicesInStock = player.performAction(&Entity::Player::getSpiceInStock, Action::EmptyActionParams{});
	auto& playerActionContext = std::get<Action::TravelActionParams>(context.playerActionParams);

	auto adjPlanetsCount = travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getAdjacentPlanetCount, dummyPlanetParams);

	return spicesInStock >= playerActionContext.spiceAmount and 
		   context.travelAgentActionParams < adjPlanetsCount;
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
