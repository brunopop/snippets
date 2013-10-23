#include "string_manip.h"
#include <iostream>

using namespace bps;
using namespace std;

int main(int argc, char* argv[])
{
	// Get user input
	cout << "Enter a phrase:" << endl;
	string phrase;
	getline(std::cin, phrase);
	cout << "Enter a delimiter:" << endl;
	string delim;
	getline(std::cin, delim);
	// Tokenize
	vector<string> tokens = split(phrase, delim.c_str()[0]);
	// Show tokens
	cout << "Tokens are:" << std::endl;
	for (auto t : tokens)
	{
		cout << t << std::endl;
	}

	return 0;
}

