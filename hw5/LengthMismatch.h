#ifndef LENGTHMISMATCH_H
#define LENGTHMISMATCH_H

#include <stdexcept>
#include <string>

using namespace std;

class LengthMismatch : public exception
{
	public:
		LengthMismatch();
		LengthMismatch(int x1, int y1);
		const char* what() const noexcept;

	private:
		string msg;
		int x;
		int y;

};
#endif