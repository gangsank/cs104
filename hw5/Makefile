CXX = g++
CPPFLAGS = -g -Wall -std=c++11

functor : functor.h functor.cpp
	$(CXX) $(CPPFLAGS) -c functor.h functor.cpp

LengthMismatch: LengthMismatch.h LengthMismatch.cpp
	$(CXX) $(CPPFLAGS) -c LengthMismatch.h LengthMismatch.cpp

Thanksgiving: LengthMismatch.o Thanksgiving.cpp
	$(CXX) $(CPPFLAGS) LengthMismatch.o Thanksgiving.cpp -o Thanksgiving

clean:
	rm -f functor LengthMismatch Thanksgiving