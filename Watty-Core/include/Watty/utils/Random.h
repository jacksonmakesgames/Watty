#pragma once
#include <random>

namespace letc {
	class Random {
	public:
		static void init() {
			Random::randomEngine = std::mt19937();
			Random::distribution = std::uniform_int_distribution<std::mt19937::result_type>();
			randomEngine.seed(std::random_device()());
		}

		static float range(float min, float max) {
			float f = (float)distribution(randomEngine) / (float)std::numeric_limits<uint32_t>::max();
			return (min + f) / (max - min);
		}
	private:
		static std::mt19937 randomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> distribution;
	};

}