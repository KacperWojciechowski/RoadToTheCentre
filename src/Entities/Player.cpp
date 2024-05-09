#include <Entities/Player.h>
#include <cassert>

namespace Entity
{
Player::Player(float startingSpiceAmount)
	: spice(startingSpiceAmount)
{
}

float Player::getSpiceAmount()
{
	return spice;
}

void Player::updateSpiceAmountBy(float amount)
{
	spice += amount;
	assert(spice >= 0);
}
} // namespace Entity
