#include <Services/GameTimeService.hpp>
#include <Core/Game.hpp>

int main()
{
	auto gts = Time::GameTimeService{};
	auto game = core::Game{ std::move(gts) };
	game.start();

	return 0;
}
