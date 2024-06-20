#include <Action/ActionValidator.hpp>
#include <Mechanics/TravelAgent.hpp>
#include <Entities/Player.hpp>
#include <GameMap/Planet.hpp>
#include <Action/GeneralAction.hpp>

namespace Action
{
namespace
{
constexpr float dummyPlanetParams = 0.0f;

bool isSellAction(const GeneralAction::Context& context)
{
	return context.planetActionCallback == &GameMap::Planet::sellSpice and 
		   context.playerActionCallback == &Entity::Player::sellSpice;
}

bool isBuyAction(const GeneralAction::Context& context)
{
	return context.planetActionCallback == &GameMap::Planet::buySpice and 
		   context.playerActionCallback == &Entity::Player::buySpice;
}

bool isTravelAction(const GeneralAction::Context& context)
{
	return context.playerActionCallback == &Entity::Player::useSpicesForTravel and 
		   context.travelAgentActionCallback == &Mechanics::TravelAgent::travelTo;
}

bool isWaitAction(const GeneralAction::Context& context)
{
	return context.isWaitAction;
}

bool validateTradeAction(
	const GeneralAction::Context& context, Mechanics::TravelAgent& travelAgent, Entity::Player& player) 
{
	if (not std::holds_alternative<TradeActionParams>(context.playerActionParams))
	{
		return false;
	}

	auto spicesInStock = player.performAction(&Entity::Player::getSpiceInStock, EmptyActionParams{});
	auto blixInStock = player.performAction(&Entity::Player::getBlixInStock, EmptyActionParams{});

	auto planetSpicesInStock = travelAgent.performActionOnCurrentPlanet(&GameMap::Planet::getSpicesInStock, dummyPlanetParams);
	auto& playerActionParams = std::get<TradeActionParams>(context.playerActionParams);
		
	if (isSellAction(context))
	{
		return spicesInStock >= context.planetActionParams
			and spicesInStock >= playerActionParams.spiceAmount;
	}
	else 
	{
		return planetSpicesInStock >= context.planetActionParams
			and planetSpicesInStock >= playerActionParams.spiceAmount
			and blixInStock >= playerActionParams.blixAmount;
	}
}

bool validateTravelAction(const GeneralAction::Context& context, Mechanics::TravelAgent& travelAgent, Entity::Player& player)
{
	if (not std::holds_alternative<TravelActionParams>(context.playerActionParams))
	{
		return false;
	}

	auto spicesInStock = player.performAction(&Entity::Player::getSpiceInStock, EmptyActionParams{});
	auto& playerActionContext = std::get<TravelActionParams>(context.playerActionParams);

	auto adjPlanetsCount = travelAgent.performActionOnCurrentPlanet(
		&GameMap::Planet::getAdjacentPlanetCount, dummyPlanetParams);

	return spicesInStock >= playerActionContext.spiceAmount and 
		   context.travelAgentActionParams < adjPlanetsCount;
}

bool validateGeneralAction(std::shared_ptr<ActionContext> context, Mechanics::TravelAgent& travelAgent, Entity::Player& player)
{
	const auto& generalActionContext = *std::dynamic_pointer_cast<GeneralAction::Context>(context);
	if (isBuyAction(generalActionContext) or isSellAction(generalActionContext))
	{
		return validateTradeAction(generalActionContext, travelAgent, player);
	}
	if (isTravelAction(generalActionContext))
	{
		return validateTravelAction(generalActionContext, travelAgent, player);
	}
	if (isWaitAction(generalActionContext))
	{
		return true;
	}
	return false;
}
} // namespace

bool Validator::validate(std::shared_ptr<ActionContext> context, Mechanics::TravelAgent& travelAgent, Entity::Player& player)
{	
	if (not context)
	{
		return false;
	}
	switch(context->type)
	{
		case ActionType::generalAction:
			return validateGeneralAction(context, travelAgent, player);
		default:
			return false;
	}
}
} // namespace Action
