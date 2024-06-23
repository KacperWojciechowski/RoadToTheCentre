#pragma once

#include <memory>
#include <Action/Action.hpp>

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
class Validator
{
public:
	static bool validate(const Action::Context&, ExecutingEntities&);
};
} // namespace Action
