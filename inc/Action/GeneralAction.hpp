#pragma once

#include <limits>
#include <cstddef>

namespace Mechanics
{
	class TravelAgent;
} // namespace Mechanics

namespace Action
{
	struct GeneralActionContext;
	enum class GeneralActionEnum : std::size_t;

constexpr std::size_t generalActionCount = 4;

GeneralActionEnum actionIdxToEnum(std::size_t actionIdx);
GeneralActionContext getActionSpecificContext(GeneralActionEnum action, Mechanics::TravelAgent& travelAgent);
} // namespace Action