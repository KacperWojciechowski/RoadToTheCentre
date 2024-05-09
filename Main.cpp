#include <Services/GameTimeService.h>
#include <Core/Game.h>

int main()
{
	auto gts = Time::GameTimeService{};
	auto game = core::Game{ std::move(gts) };
	game.start();

	return 0;
}
