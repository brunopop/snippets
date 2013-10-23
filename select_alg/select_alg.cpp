#include "select_alg.h"

using namespace bps;

int main(int argc, char* argv[])
{
	// Find the weighted median of an array in O(n) time
	int elems[] = {10, -20, 9, 8, 15, -12, 6, 5, 4, 2, -5, 3, 1};
	double weights[] = {0.01, 0.2, 0.1, 0.05, 0.03, 0.01, 0.21, 0.17, 0.03, 0.03, 0.1, 0.04, 0.02};
	int weighted_median = FindWeightedMedian(std::vector<int>(elems, elems+sizeof(elems)/sizeof(int)),
												std::vector<double>(weights, weights+sizeof(weights)/sizeof(double)), 0.0);

	return 0;
}

