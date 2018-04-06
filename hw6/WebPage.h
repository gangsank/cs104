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
		void parse(vector<WebPage*>);
		string get_filename();
		set<WebPage*> get_inLinks();
		set<WebPage*> get_outLinks();
		int get_inLinksSize();
		int get_outLinksSize();
		void add_inLink(WebPage*);
		void add_outLink(WebPage*);
		string get_raw();
		set<string> get_content();
		void print_parsed();
		void set_visited();
		void set_unvisited();
		bool get_visited();
		double get_rank();
		void set_rank(double num);

	private:
		string filename;
		string raw="";
		set<string> content;
		set<WebPage*> inLinks;
		set<WebPage*> outLinks;
		bool visited;
		double rank;
};
#endif