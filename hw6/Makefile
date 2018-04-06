CXX = g++
CPPFLAGS = -g -Wall -std=c++11

WebPage.o : WebPage.h WebPage.cpp
	$(CXX) $(CPPFLAGS) -c WebPage.h WebPage.cpp

Manager.o: Manager.h Manager.cpp
	$(CXX) $(CPPFLAGS) -c Manager.h Manager.cpp

crawler: WebPage.o crawler.cpp
	$(CXX) $(CPPFLAGS) WebPage.o crawler.cpp -o crawler

search: WebPage.o Manager.o search.cpp
	$(CXX) $(CPPFLAGS) WebPage.o Manager.o search.cpp -o search

clean:
	rm -f WebPage.o Manager.o search crawler