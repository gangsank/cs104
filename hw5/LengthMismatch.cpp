#include "LengthMismatch.h"

LengthMismatch::LengthMismatch()
{

}

LengthMismatch::LengthMismatch(int x1, int y1)
{
	x=x1;
	y=y1;
	msg = "Input data structures have lengths ["
	+ to_string(x) +"] and [" + to_string(y) +"]";
}

const char* LengthMismatch::what() const noexcept
{
   return msg.c_str();
}