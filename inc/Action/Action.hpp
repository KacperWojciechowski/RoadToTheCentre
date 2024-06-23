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

class Action
{
public:
    struct Context
    {
        Context(ActionType actionType)
            : actionType(actionType)
        {
        }
        virtual ~Context() = default;

        ActionType actionType;
    };

    virtual std::size_t getActionCount()
    {
        return 0;
    }

    virtual void prepareActionSpecificContext(std::size_t action, ExecutingEntities executingEntities) = 0;
    virtual void execute(ExecutingEntities) = 0;
    virtual const Context& getContext() const = 0;

    virtual ~Action() = default;
};
} // namespace Action