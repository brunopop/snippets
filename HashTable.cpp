// Author: Bruno Pop-Stefanov
// Date: 9/15/2013
// Description: Example of implementation of a hash table.

#include <iostream>
#include <string>

#include "HashTable.h"

#define TABLE_SIZE 65536
#define null_k -1
#define null_v ""

class MyHashTable : public HashTable<int, std::string>
{
	int hash(int &key)
	{
		return key;
	};

	bool compare_keys(int &key1, int key2)
	{
		return key1 == key2;
	};

public:
	MyHashTable(int size) : HashTable<int, std::string>(size) {};
};


int main(int argc, char* argv[])
{
	// Create empty table
	MyHashTable myTable(256);

	// Add entries
	int key = 10;
	std::string value("I am 10.");
	myTable.add(key, value);
	key = 12;
	value = "I am 12.";
	myTable.add(key, value);

	// Get value from key
	std::string looked_up = myTable.get(key);
	std::cout << "The value of key " << key << " is: " << looked_up << std::endl;

	// Remove an entry
	key = 10;
	myTable.remove(key);

	// Set an entry
	key = 12;
	value = "I am now 12 bis.";
	myTable.set(key, value);

	// Retrieve
	looked_up = myTable.get(key);
	std::cout << "The value of key " << key << " is: " << looked_up << std::endl;

	return 0;
}

