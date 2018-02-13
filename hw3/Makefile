CXX = g++
CPPFLAGS = -g -Wall

stackstr.o : stackstr.h stackstr.cpp
	$(CXX) $(CPPFLAGS) -c stackstr.h stackstr.cpp

lliststr.o : lliststr.h lliststr.cpp
	$(CXX) $(CPPFLAGS) -c lliststr.h lliststr.cpp

stringparser: stackstr.o lliststr.o stringparser.cpp
	$(CXX) $(CPPFLAGS) stackstr.o lliststr.o stringparser.cpp -o stringparser

clean:
	rm -f stackstr.o lliststr.o stringparser