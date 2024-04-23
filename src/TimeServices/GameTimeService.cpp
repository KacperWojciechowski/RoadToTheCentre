#include <TimeServices/GameTimeService.h>

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
		subscribers.erase(std::find_if(subscribers.begin(), subscribers.end(), [target](const auto& s) {
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
