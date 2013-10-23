#include "math.h"

using namespace bps;

int main(int argc, char* argv[])
{
	// Goldbach's conjecture
	int n = 41;
	int p = 0, q = 0;
	bool isGoldbach = GoldbachsConjecture(n, &p, &q);

	// Max subsequence
	int array[] = {10, -20, 9, 8, 3, -12, 6, 3, 4, 1, -5, 3, 1};
	std::vector<int> arr(array, array+sizeof(array)/sizeof(int));
	int begin = 0, end = 0;
	int res = maxSubsequence(arr, begin, end);

	return 0;
}

