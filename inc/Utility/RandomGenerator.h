#pragma once

#include <random>

namespace utility
{
class RandomGenerator
{
public:
	static int getInt(int lowerBound, int upperBound)
	{
		RandomEngine gen(randomDevice());
		std::uniform_int_distribution<> distribution (lowerBound, upperBound);
		return distribution(gen);
	}
	
	static float getFloat(float lowerBound, float upperBound)
	{
		RandomEngine gen(randomDevice());
		std::uniform_real_distribution<> distribution(lowerBound, upperBound);
		return static_cast<float>(distribution(gen));
	}
private:
	using RandomEngine = std::mt19937;

	static std::random_device randomDevice;
};
} // namespace utility
