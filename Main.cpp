#include <iostream>
#include <TimeServices/GameTimeService.h>
#include <GameMap/Planet.h>

int main()
{
	auto gts = Time::GameTimeService{};
	auto p1 = GameMap::Planet::create(1, gts);
	auto p2 = GameMap::Planet::create(1, gts);
	{
		auto p3 = GameMap::Planet::create(1, gts);

		for (int i = 0; i < 10; i++)
		{
			system("cls");
			std::cout << *p1 << *p2 << *p3;
			p1->buySpice(1);
			p2->buySpice(1);
			p3->buySpice(1);
			std::cin.get();
			gts.update();
		}
	}
	gts.unsubscribe(p2);
	for (int i = 0; i < 10; i++)
	{
		system("cls");
		std::cout << *p1 << *p2;
		p1->buySpice(1);
		p2->buySpice(1);
		std::cin.get();
		gts.update();
	}

	return 0;
}
