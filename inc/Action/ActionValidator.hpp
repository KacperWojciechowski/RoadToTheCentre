#pragma once

#include <Action/GeneralActionContext.hpp>

namespace Action
{
class Validator
{
public:
	static bool validate(const GeneralActionContext&, Mechanics::TravelAgent&, Entity::Player&);
};
} // namespace Action
