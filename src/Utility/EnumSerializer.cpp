#include <Utility/EnumSerializer.h>

#include <string>
#include <GameMap/AdjacencyType.h>

namespace utility
{
std::string EnumSerializer<GameMap::AdjacencyType>::operator()()
{
	switch (val)
	{
	case GameMap::AdjacencyType::intraSystem:
		return "intraSystem";
	case GameMap::AdjacencyType::interStelar:
		return "interStelar";
	default:
		return "";
	}
}
}
