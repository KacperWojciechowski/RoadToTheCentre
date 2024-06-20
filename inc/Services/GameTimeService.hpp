#pragma once
#include <Services/ITimeObserver.hpp>
#include <vector>
#include <memory>

namespace Time
{
class GameTimeService
{
public:
	void subscribe(std::shared_ptr<ITimeObserver>);
	void unsubscribe(std::shared_ptr<ITimeObserver>);
	void update();
public:
	std::vector<std::weak_ptr<ITimeObserver>> subscribers = {};
};
} // namespace Time
