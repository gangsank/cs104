#ifndef FUNCTOR_H
#define FUNCTOR_H

#include <string>
#include <iostream>

using namespace std;

class NumStrComp
{
	public:
		bool operator()(const string& lhs, const string& rhs);
};
#endif