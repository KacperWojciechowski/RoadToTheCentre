#pragma once

#include <string>
#include <GameMap/AdjacencyType.h>

namespace utility
{
template<typename EnumType>
class EnumSerializer
{
public:
	EnumSerializer(EnumType val) : val(val) {}

	inline std::string operator()() { return ""; }
private:
	const EnumType val;
};

inline std::string EnumSerializer<GameMap::AdjacencyType>::operator()()
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
} // namespace utility
