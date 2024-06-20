#pragma once

#include <cstddef>
#include <memory>

namespace Mechanics
{
class TravelAgent;
} // namespace Mechanics

namespace Action
{
enum class ActionType
{
    undefined = 0,
    generalAction = 1
};

struct EmptyActionParams
{
};

struct ActionContext
{
    ActionContext()
        : type(ActionType::undefined)
    {}

    ActionContext(ActionType actionType)
        : type(actionType)
    {}

    virtual ~ActionContext() = default;

    ActionType type;
};

class Action
{
    virtual std::shared_ptr<ActionContext> getActionSpecificContext(std::size_t action, Mechanics::TravelAgent& travelAgent)
    {
        return nullptr;
    }

    virtual std::size_t getActionCount()
    {
        return 0;
    }
};
} // namespace Action