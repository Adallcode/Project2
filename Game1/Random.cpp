#include "Random.h"

std::mt19937 Random::mGenerator;

void Random::Init()
{
	std::random_device rd;

	mGenerator.seed(rd());
}

float Random::FloatInRange(float min, float max)
{
	std::uniform_real_distribution<float> d(min, max);
	return d(mGenerator);
}
