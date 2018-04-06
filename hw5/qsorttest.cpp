#include "qsort.h"
#include <iostream>

int main()
{
	std::vector<int> testcase1;
	testcase1.push_back(1);
	testcase1.push_back(3);
	testcase1.push_back(5);
	testcase1.push_back(7);
	testcase1.push_back(2);
	testcase1.push_back(4);
	testcase1.push_back(6);
	testcase1.push_back(8);
	testcase1.push_back(9);
	testcase1.push_back(10);

	QuickSort(testcase1, std::less<int>());

	for (unsigned int i=0; i<testcase1.size(); i++)
	{
		std::cout << testcase1[i] << std::endl;
	}

	std::cout << std::endl;
	QuickSort(testcase1,std::greater<int>());

	for (unsigned int i=0; i<testcase1.size(); i++)
	{
		std::cout << testcase1[i] << std::endl;
	}
}