#pragma once

#include <UI/ActionContext.h>

namespace Action
{
class Validator
{
public:
	static bool validate(const ActionContext&, Mechanics::TravelAgent&, Entity::Player&);
};
} // namespace Action
