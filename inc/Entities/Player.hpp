#pragma once

#include <iostream>
#include <variant>

namespace Action
{
struct EmptyActionParams;
struct TradeActionParams;
struct TravelActionParams;

using PlayerActionParams = std::variant<
	EmptyActionParams,
	TradeActionParams,
	TravelActionParams>;
}

namespace Entity
{
class Player
{
public:
	Player(float);

	Player(const Player&) = delete;
	Player(Player&&) = delete;
	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&) = delete;

	friend std::ostream& operator<<(std::ostream&, const Player&);

	using PlayerActionCallback = float(Entity::Player::*)(const Action::PlayerActionParams&);
	float performAction(PlayerActionCallback, const Action::PlayerActionParams&);
	
	float buySpice(const Action::PlayerActionParams&);
	float sellSpice(const Action::PlayerActionParams&);
	float getSpiceInStock(const Action::PlayerActionParams&);
	float getBlixInStock(const Action::PlayerActionParams&);
	float useSpicesForTravel(const Action::PlayerActionParams&);

private:
	void updateSpiceAmountBy(float);
	void updateBlixAmountBy(float);

	float spice = 0.0f;
	float blix = {};
};
} // namespace Entity
