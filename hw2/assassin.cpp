#include "lliststr.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main (int argc, char* argv[])
{
	ifstream input(argv[1]);

	LListStr* list = new LListStr();
	string command;
	int pos;
	string str;

	while (input >> command)
	{
		if (command == "ADD")
		{
			input >> pos;
			input >> str;
			list->insert(pos,str);
		}

		else if (command == "ACT")
		{
			input >> pos;
			
			if(pos < list->size())
			{
			cout << "Assassinated: " << list->get(pos-1) << endl;
			list->remove(pos-1);
			}
		}
	}

	if(list->size() == 1)
	{
		cout << "Winner: " << list->get(0) << endl;
	}

	else
	{
		cout << "Remaining Players: " << list->size() << endl;
		for (int i=0; i<list->size(); i++)
		{
			cout << list->get(i)<<endl;
		}
	}

	delete list;
}
