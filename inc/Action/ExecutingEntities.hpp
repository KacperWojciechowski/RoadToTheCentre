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
    Entity::Player& player;
    Mechanics::TravelAgent& travelAgent;
};
} // namespace Action