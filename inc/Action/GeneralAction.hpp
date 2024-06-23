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
	using ActionIdx = std::size_t;

	struct Context : public Action::Context
	{
		Context()
			: Action::Context(ActionType::generalAction)
			, planetActionCallback(nullptr)
			, playerActionCallback(nullptr)
			, travelAgentActionCallback(nullptr)
			, playerActionParams(EmptyActionParams{})
			, planetActionParams(0.0f)
			, travelAgentActionParams(0u)
			, isWaitAction(false)
		{}
		Context(const Context&) = default;
		Context(Context&&) = default;

		Context& operator=(const Context&) = default;
		Context& operator=(Context&&) = default;

		~Context() = default;

		Mechanics::TravelAgent::PlanetActionCallback planetActionCallback;
		Entity::Player::PlayerActionCallback playerActionCallback;
		Mechanics::TravelAgent::TravelAgentActionCallback travelAgentActionCallback;
		
		PlayerActionParams playerActionParams;
		float planetActionParams;
		std::size_t travelAgentActionParams;
		
		bool isWaitAction = false;
	};

	const Action::Context& getContext() const override;
	void execute(ExecutingEntities) override;
	void prepareActionSpecificContext(ActionIdx, ExecutingEntities) override;
	std::size_t getActionCount() override;

private:
	enum class Enum : std::size_t;

	Enum actionIdxToEnum(std::size_t);
	void prepareWaitSpecificContext();
	void prepareTravelSpecificContext(ExecutingEntities executingEntities);
	void prepareSellSpecificContext(ExecutingEntities executingEntities);
	void prepareBuySpecificContext(ExecutingEntities executingEntities);

	Context context;
	static constexpr std::size_t actionCount = 4;
};
} // namespace Action