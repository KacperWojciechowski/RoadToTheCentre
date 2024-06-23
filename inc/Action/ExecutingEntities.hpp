#pragma once

namespace Entity
{
class Player;
} // namespace Entity

namespace Mechanics
{
class TravelAgent;
} // namespace Mechanics

namespace Time
{
class GameTimeService;
} // namespace Time

namespace Action
{
struct ExecutingEntities
{
    ExecutingEntities(Entity::Player& player, Mechanics::TravelAgent& travelAgent, Time::GameTimeService& timeService)
        : player(player)
        , travelAgent(travelAgent)
        , timeService(timeService)
    {}
    ~ExecutingEntities() = default;

    Entity::Player& player;
    Mechanics::TravelAgent& travelAgent;
    Time::GameTimeService& timeService;
};
} // namespace Action