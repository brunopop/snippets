#include "search_alg.h"
#include <iostream>

using namespace bps;
using namespace std;

int main(int argc, char* argv[])
{
	int array[32] = {-25, -24, -23, -20, -15, -10, -7, -5, -3, -2, 0, 3, 4, 5, 8, 11, 15, 16, 19, 20, 25, 27, 28, 29, 30, 35, 36, 37, 38, 39, 40, 41};
	cout << "Array is:\n\t";
	for (auto i : array) cout << i << ", ";
	cout << "\n\nEnter a number:" << endl;
	int n;
	cin >> n;
	int index = BinarySearch(n, array, 0, 31);
	if (index == -1)
		cout << n << " was not found in the array." << endl;
	else
		cout << "The index of " << n << " is: " << index << endl;

	return 0;
}

