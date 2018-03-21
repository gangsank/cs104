#include "functor.h"

template <class Comparator>
void DoStringCompare(const string& s1, const string& s2, Comparator comp)
{
	cout << comp(s1, s2) << endl;  
}

int main()
{
	string s1 = "Blue";
	string s2 = "Redfdsfe";

	functor::NumStrComp Ncomp;

	DoStringCompare(s1,s2,Ncomp);
}