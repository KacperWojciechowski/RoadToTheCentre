#pragma once

namespace Time
{
class ITimeObserver
{
public:
	virtual void tick() = 0;
};
} // namespace Time
