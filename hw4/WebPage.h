#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <string>
#include <cstring>
#include <fstream>
#include <set>
#include <iostream>
#include <cctype>
#include <map>
#include <vector>
#include <utility>

using namespace std;

class WebPage
{
	public:
		WebPage();
		WebPage(string name);
		WebPage(const char* link);
		~WebPage();
		void print_content(ofstream&);
		void parse(const vector<WebPage*>);
		string get_filename();
		set<WebPage*> get_inLinks();
		set<WebPage*> get_outLinks();
		void add_inLink(WebPage*);
		void add_outLink(WebPage*);
		string get_raw();
		set<string> get_content();
		void print_parsed();

	private:
		string filename;
		string raw="";
		set<string> content;
		set<WebPage*> inLinks;
		set<WebPage*> outLinks;
};
#endif