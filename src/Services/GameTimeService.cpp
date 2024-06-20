#include <Services/GameTimeService.hpp>
#include <algorithm>

namespace Time
{
	void GameTimeService::subscribe(std::shared_ptr<ITimeObserver> target)
	{
		for (auto& s : subscribers)
		{
			auto subscriber = s.lock();
			if (subscriber and subscriber == target)
			{
				return;
			}
		}
		subscribers.emplace_back(target);
	}
	void GameTimeService::unsubscribe(std::shared_ptr<ITimeObserver> target)
	{
		subscribers.erase(std::ranges::find_if(subscribers, [target](const auto& s) {
			auto subscriber = s.lock();
			return subscriber and subscriber == target;
		}));
	}
	void GameTimeService::update()
	{
		for (auto& s : subscribers)
		{
			auto subscriber = s.lock();
			if (subscriber)
			{
				subscriber->tick();
			}
		}
	}
} // namespace Time
