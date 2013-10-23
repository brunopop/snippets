#include "bit_manip.h"
#include <iostream>

using namespace bps;
using namespace std;

int main(int argc, char* argv[])
{
	cout << "Enter a number:" << endl;
	int n;
	cin >> n;
	cout << n << " has " << count_bits(n) << " set bits." << endl;
	return 0;
}

