#pragma once

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

	float getSpiceAmount();
	void updateSpiceAmountBy(float amount);

private:
	float spice = 0.0f;
};
} // namespace Entity
