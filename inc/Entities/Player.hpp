#pragma once

#include <iostream>
#include <variant>

namespace Action
{
struct EmptyActionContext
{
};

struct PlayerTradeActionContext
{
	float spiceAmount;
	float blixAmount;
};

struct PlayerTravelActionContext
{
	float spiceAmount;
};

using PlayerActionContext = std::variant<
	EmptyActionContext,
	PlayerTradeActionContext,
	PlayerTravelActionContext>;
} // namespace Action

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

	using PlayerActionCallback = float(Entity::Player::*)(const Action::PlayerActionContext&);
	float performAction(PlayerActionCallback, const Action::PlayerActionContext&);
	
	float buySpice(const Action::PlayerActionContext&);
	float sellSpice(const Action::PlayerActionContext&);
	float getSpiceInStock(const Action::PlayerActionContext&);
	float getBlixInStock(const Action::PlayerActionContext&);
	float useSpicesForTravel(const Action::PlayerActionContext&);

private:
	void updateSpiceAmountBy(float);
	void updateBlixAmountBy(float);

	float spice = 0.0f;
	float blix = {};
};
} // namespace Entity
