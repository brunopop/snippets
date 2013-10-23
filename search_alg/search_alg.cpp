#include "search_alg.h"
#include <iostream>

using namespace bps;

int main(int argc, char* argv[])
{
	int array[32] = {-25, -24, -23, -20, -15, -10, -7, -5, -3, -2, 0, 3, 4, 5, 8, 11, 15, 16, 19, 20, 25, 27, 28, 29, 30, 35, 36, 37, 38, 39, 40, 41};
	std::cout << "Array is:\n\t";
	for (auto i : array)
	{
		std::cout << i << ", ";
	}
	std::cout << "\n\nEnter a number:" << std::endl;
	int n;
	std::cin >> n;
	int index = FindIndex(array, 0, n);
	std::cout << "The index of " << n << " is: " << index << std::endl;

	return 0;
}

