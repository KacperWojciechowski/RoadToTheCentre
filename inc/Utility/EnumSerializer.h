#pragma once

#include <string>

namespace utility
{
template<typename EnumType>
class EnumSerializer
{
public:
	EnumSerializer(EnumType val) : val(val) {}

	std::string operator()() {}
private:
	const EnumType val;
};
} // namespace utility
