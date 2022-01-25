#include <utils/Random.h>

namespace watty {
	std::mt19937_64 Random::randomEngine = std::mt19937_64();
	std::uniform_int_distribution<std::mt19937::result_type> Random::distribution = std::uniform_int_distribution<std::mt19937::result_type>();
}