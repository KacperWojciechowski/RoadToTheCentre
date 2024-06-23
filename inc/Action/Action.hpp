#pragma once

#include <cstddef>
#include <memory>
#include <Action/ExecutingEntities.hpp>

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
public:
    virtual std::shared_ptr<ActionContext> getActionSpecificContext(std::size_t action, ExecutingEntities executingEntities)
    {
        return nullptr;
    }

    virtual std::size_t getActionCount()
    {
        return 0;
    }

    virtual void execute(std::shared_ptr<ActionContext> context) = 0;
    
    virtual ~Action() = default;
};
} // namespace Action