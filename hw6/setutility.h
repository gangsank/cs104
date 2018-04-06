#include<set>

template <typename T>
std::set<T> intersectSet(std::set<T> result1, std::set<T> result2)
{
	typename std::set<T>::iterator it1;
	typename std::set<T>::iterator it2;
	typename std::set<T> intersect;

	for (it1 = result1.begin(); it1 != result1.end(); ++it1)
	{
		for (it2 = result2.begin(); it2 != result2.end(); ++it2)
		{
			if (*it1==*it2)
			{
				intersect.insert(*it1);
			}
		}
	}

	return intersect;
}

template <typename T>
std::set<T> unionSet(std::set<T> result1, std::set<T> result2)
{
	typename std::set<T>::iterator it1;
	typename std::set<T>::iterator it2;
	typename std::set<T> uni;

	for (it1 = result1.begin(); it1 != result1.end(); ++it1)
	{
		uni.insert(*it1);
	}	
	
	for (it2 = result2.begin(); it2 != result2.end(); ++it2)
	{
		uni.insert(*it2);
	}		
	
	return uni;
}