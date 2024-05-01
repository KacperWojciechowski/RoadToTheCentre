#include <iostream>
#include <TimeServices/GameTimeService.h>
#include <GameMap/SolarSystem.h>

int main()
{
	auto gts = Time::GameTimeService{};
	auto system = GameMap::SolarSystem::create(gts);

	for (int i = 0; i < 10; i++)
	{
		std::cout << *system << std::endl;
		for (int i = 0; i < system->getPlanetCount(); i++)
		{
			(*system)[i]->buySpice(1);
		}
		gts.update();
	}

	return 0;
}
