#ifndef CACHE_LRU_H
#define CACHE_LRU_H

#include "splayTree.h"
#include <stdexcept>

template<typename Key, typename Value>
class cacheLRU
{
public:
	cacheLRU(int capacity);
	~cacheLRU();
	void put(const std::pair<const Key, Value>& keyValuePair);
	std::pair<const Key, Value> get(const Key& key);

	//for cache analysis
	//int get_lcount();
	//int get_rcount();
	//int cachemiss;

private:
	int cap;
	SplayTree<Key,Value>* tree;
	int cache;
};

template<typename Key, typename Value>
cacheLRU<Key,Value>::cacheLRU(int capacity)
{
	cap = capacity;
	cache = 0;
	//cachemiss = 0;
	tree = new SplayTree<Key,Value>();
}

template<typename Key, typename Value>
cacheLRU<Key,Value>::~cacheLRU()
{
	delete tree;
}

template<typename Key, typename Value>
void cacheLRU<Key,Value>::put (const std::pair<const Key, Value>& keyValuePair)
{
	if (cache == cap)
	{
		tree->deleteMinLeaf();
		cache--;
		//cachemiss++;
	}

	tree->insert(keyValuePair);
	cache++;
}

template<typename Key, typename Value>
std::pair<const Key,Value> cacheLRU<Key,Value>::get (const Key& key)
{
	if(tree->find(key) == tree->end())
	{
		throw std::logic_error ("Error");
	}

	return *(tree->find(key));
}

/*
template<typename Key, typename Value>
int cacheLRU<Key,Value>::get_lcount()
{
	return tree->LeftRotateCount;
}

template<typename Key, typename Value>
int cacheLRU<Key,Value>::get_rcount()
{
	return tree->RightRotateCount;
}
*/
;
#endif