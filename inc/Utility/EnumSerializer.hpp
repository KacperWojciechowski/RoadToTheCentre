#pragma once

#include <string>
#include <GameMap/AdjacencyType.hpp>

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

template<>
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
