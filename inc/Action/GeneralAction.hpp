#pragma once

#include <Action/Action.hpp>
#include <limits>
#include <cstddef>
#include <Mechanics/TravelAgent.hpp>
#include <Entities/Player.hpp>

namespace Action
{
struct TradeActionParams
{
	float spiceAmount;
	float blixAmount;
};

struct TravelActionParams
{
	float spiceAmount;
};

class GeneralAction final : public Action
{
public:
	enum class Enum : std::size_t;

	struct Context final : public ActionContext
	{
		Context()
			: ActionContext(ActionType::generalAction)
			, planetActionCallback(nullptr)
			, playerActionCallback(nullptr)
			, travelAgentActionCallback(nullptr)
			, playerActionParams(EmptyActionParams{})
			, planetActionParams(0.0f)
			, travelAgentActionParams(0u)
			, isWaitAction(false)
		{}

		~Context() = default;

		Mechanics::TravelAgent::PlanetActionCallback planetActionCallback;
		Entity::Player::PlayerActionCallback playerActionCallback;
		Mechanics::TravelAgent::TravelAgentActionCallback travelAgentActionCallback;
		
		PlayerActionParams playerActionParams;
		float planetActionParams;
		std::size_t travelAgentActionParams;
		
		bool isWaitAction = false;

	};

	std::shared_ptr<ActionContext> getActionSpecificContext(std::size_t action, ExecutingEntities executingEntities) override;
	std::size_t getActionCount() override;

private:
	static constexpr std::size_t actionCount = 4;
};
} // namespace Action