#include <utils/Random.h>

namespace letc {
	std::mt19937 Random::randomEngine = std::mt19937();
	std::uniform_int_distribution<std::mt19937::result_type> Random::distribution = std::uniform_int_distribution<std::mt19937::result_type>();
}