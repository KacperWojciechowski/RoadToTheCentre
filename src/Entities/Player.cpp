#include <Entities/Player.hpp>
#include <Utility/RandomGenerator.hpp>
#include <iostream>
#include <Action/GeneralActionContext.hpp>

namespace
{
float randomizeStartingBlix()
{
	constexpr float lowerBound = 1000.0f;
	constexpr float upperBound = 5000.0f;
	return utility::RandomGenerator::getFloat(lowerBound, upperBound);
}
} // namespace::

namespace Entity
{
Player::Player(float startingSpiceAmount)
	: spice(startingSpiceAmount)
	, blix(randomizeStartingBlix())
{
}

float Player::performAction(PlayerActionCallback action, const Action::PlayerActionParams& context)
{
	if (not action)
	{
		return 0.0f;
	}
	return (this->*action)(context);
}

float Player::buySpice(const Action::PlayerActionParams& context)
{
	if (not std::holds_alternative<Action::TradeActionParams>(context))
	{
		throw std::invalid_argument("Invalid context provided for [Player::buySpice()]");
	}
	const auto& tgtContext = std::get<Action::TradeActionParams>(context);

	if (tgtContext.spiceAmount < 0 or tgtContext.blixAmount < 0)
	{
		throw std::invalid_argument("Negative amount of spice or blix provided");
	}

	updateSpiceAmountBy(tgtContext.spiceAmount);
	updateBlixAmountBy(-1 * tgtContext.blixAmount);
	return 0.0f;
}

float Player::sellSpice(const Action::PlayerActionParams& context)
{
	if (not std::holds_alternative<Action::TradeActionParams>(context))
	{
		throw std::invalid_argument("Invalid context provided for [Player::sellSpice()]");
	}
	const auto& tgtContext = std::get<Action::TradeActionParams>(context);

	if (tgtContext.spiceAmount < 0 or tgtContext.blixAmount < 0)
	{
		throw std::invalid_argument("Negative amount of spice or blix provided");
	}

	updateSpiceAmountBy(-1 * tgtContext.spiceAmount);
	updateBlixAmountBy(tgtContext.blixAmount);
	return 0.0f;
}

float Player::getSpiceInStock(const Action::PlayerActionParams&)
{
	return spice;
}

float Player::getBlixInStock(const Action::PlayerActionParams&)
{
	return blix;
}

float Player::useSpicesForTravel(const Action::PlayerActionParams& context)
{
	if (not std::holds_alternative<Action::TravelActionParams>(context))
	{
		throw std::invalid_argument("Invalid context provided for [Player::useSpicesForTravel()]");
	}
	const auto& tgtContext = std::get<Action::TravelActionParams>(context);

	if (tgtContext.spiceAmount < 0)
	{
		throw std::invalid_argument("Negative amount of spice provided");
	}

	updateSpiceAmountBy(-1 * tgtContext.spiceAmount);
	return 0.0f;
}

void Player::updateSpiceAmountBy(float amount)
{
	if (spice + amount < 0)
	{
		throw std::invalid_argument("Updating spice would lead to negative balance");
	}
	spice += amount;
}

void Player::updateBlixAmountBy(float amount)
{
	if (blix + amount < 0)
	{
		throw std::invalid_argument("Updating blix would lead to negative balance");
	}
	blix += amount;
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
	out << "Player's Blix amount = " << player.blix << "\n";
	out << "Player's spice amount = " << player.spice << "\n";
	return out;
}
} // namespace Entity
