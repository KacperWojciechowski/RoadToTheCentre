#pragma once

#include <memory>

namespace Mechanics
{
class TravelAgent;
} // namespace Mechanics

namespace Entity
{
class Player;
} // namespace Entity

namespace Action
{
class ActionContext;

class Validator
{
public:
	static bool validate(std::shared_ptr<ActionContext>, Mechanics::TravelAgent&, Entity::Player&);
};
} // namespace Action
