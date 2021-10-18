#pragma once

#include <random>

class Random
{
public:
	static void Init();

	static float FloatInRange(float min, float max);

private:
	static std::mt19937 mGenerator;

};

