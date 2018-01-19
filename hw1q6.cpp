#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void rec_streams (ifstream& ifile, int num)
{
	string word;
	stringstream ss;

	if (num==1)
	{
		ifile >> word;
		cout << word << " ";
	}

	else
	{
		ifile >> word;
		ss << word;

		rec_streams (ifile, --num);
		cout << word << " ";
	}
}

int main (int argc, char* argv[])
{
	ifstream ifile;
	ifile.open(argv[1]);

	int num;

	ifile >> num;

	rec_streams (ifile, num);

	cout << endl;

  	return 0;
}
