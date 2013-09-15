// Author: Bruno Pop-Stefanov
// Date: 9/15/2013
// Description: Template hash table implementation.
// The user must define his/her own hash table subclass
// and override the hash function and compare_keys method.
// He/she should also define a null_k and null_v constants
// for empty entries, depending on the type of key and value.

template<typename K, typename V> struct Node
{
	Node<K,V> *prev_node;
	Node<K,V> *next_node;
	K key;
	V value;
};

// Abstract template class
// User must override the private hash function
// and the method to compare keys in the subclass
template<typename K, typename V> class HashTable
{
	Node<K,V> **buckets;
	int num_entries;
	int size;

	virtual int hash(K &key) = 0;
	virtual bool compare_keys(K &key1, K key2) = 0;

	Node<K,V>* search_node(K key)
	{
		int index = hash(key);
		Node<K,V> *root = buckets[index];
		return search_recursive(root, key);
	};

	Node<K,V>* search_recursive(Node<K,V> *node, K &key)
	{
		if (compare_keys(node->key, key))
		{
			return node;
		}
		else if (node->next_node != nullptr)
		{
			return search_recursive(node->next_node, key);
		}
		else
		{
			return nullptr;
		}
	};

	// Reallocate the table when the number of entries
	// is large compared to the number of buckets
	void reallocate(int size)
	{
	};

	// Recursively erase all nodes in a linked list
	void erase_llist(Node<K,V> *node)
	{
		// Parse all nodes in linked list
		while (node->next_node != nullptr)
		{
			erase_llist(node->next_node);
		}
		delete node;
		node = nullptr;
	};

public:
	HashTable(int size) : size(size), num_entries(0)
	{
		buckets = new Node<K,V>*[size];
		// Initialize all buckets to empty nodes
		for (int i=0; i<size; i++)
		{
			buckets[i] = new Node<K,V>;
			buckets[i]->next_node = nullptr;
			buckets[i]->prev_node = nullptr;
			buckets[i]->key = null_k;
			buckets[i]->value = null_v;
		}
	};

	~HashTable()
	{
		// For each bucket, delete all nodes in linked list
		for (int i=0; i<size; i++)
		{
			Node<K,V> *node = buckets[i];
			// If linked list exists
			if (node != nullptr)
			{
				erase_llist(node);
			}
		}
	};

	// Add the <key,value> pair
	void add(K &key, V &value)
	{
		// Search if <key,value> pair does not already exist
		Node<K,V> *unique = search_node(key);
		// If it does not, then add the pair
		if (unique == nullptr)
		{
			int index = hash(key);
			// If no collision
			if (compare_keys(buckets[index]->key, null_k))
			{
				// Add a new node containing <key,value>
				buckets[index]->key = key;
				buckets[index]->value = value;
			}
			else
			{
				Node<K,V> *node = buckets[index];
				// While there is a next node
				while (node->next_node != nullptr)
				{
					// Move forward until last node is reached
					node = node->next_node;
				}
				// Add node with <key,value> pair
				node->next_node = new Node<K,V>;
				node->next_node->prev_node = node->prev_node;
				node->next_node->next_node = nullptr;
				node->next_node->key = key;
				node->next_node->value = value;
			}
			num_entries++;
		}
	};

	// Remove the entry corresponding to key
	void remove(K &key)
	{
		// Find unique node corresponding to key
		Node<K,V> *node = search_node(key);
		// If it exists
		if (node != nullptr)
		{
			// If it is not the last in the linked list
			if (node->next_node != nullptr)
			{
				// And if it is not the first in the linked list
				if (node->prev_node != nullptr)
				{
					// Link previous and next nodes together
					node->prev_node->next_node = node->next_node;
					node->next_node->prev_node = node->prev_node;
				}
				else
				{
					// Else simply move the next node to the first position
					buckets[hash(key)] = node->next_node;
					node->next_node->prev_node = nullptr;
				}
			}
			// If it is not the first
			if (node->prev_node != nullptr)
			{
				node->prev_node->next_node = nullptr;
				delete node;
				node = nullptr;
			}
			else
			{
				// If it is, then set entry table to nullptr
				// Otherwise the destructor will try to free
				// memory that has already been free
				delete node;
				node = nullptr;
				buckets[hash(key)] = nullptr;
			}
			num_entries--;
		}
	};

	// Return the value of key
	V get(K &key)
	{
		// Find unique node corresponding to key
		Node<K,V> *node = search_node(key);
		// If it exists
		if (node != nullptr)
		{
			return node->value;
		}
		else
		{
			// return null if there is no <key,value> pair in the table
			return null_v;
		}
	};

	// Set a new value for key
	void set(K &key, V &value)
	{
		// Find unique node corresponding to key
		Node<K,V> *node = search_node(key);
		// If it exists
		if (node != nullptr)
		{
			// Replace old value with new one
			node->value = value;
		}
	};

};