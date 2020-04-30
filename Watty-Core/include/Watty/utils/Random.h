#pragma once
#include <random>
#include <float.h>
namespace letc {
	class Random {
	public:
		static void init() {
			Random::randomEngine = std::mt19937_64();
			Random::distribution = std::uniform_int_distribution<std::mt19937::result_type>();
			randomEngine.seed(std::random_device()());
		}

		//TODO: Move to cpp
		static float range(float min, float max) {
			float random = (float)distribution(randomEngine);
			float distMax = (float)Random::distribution.b();
			random /= distMax;
			float diff = max - min;
			float r = random * diff;
			return min + r;
		}
	private:
		static std::mt19937_64 randomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> distribution;
	};

}