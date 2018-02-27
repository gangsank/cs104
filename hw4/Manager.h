#ifndef MANAGER_H
#define MANAGER_H

#include "WebPage.h"

class Manager
{
	public:
		Manager();
		Manager(vector<WebPage*>);
		set<WebPage*> do_search(string);
		set<WebPage*> intersectWebPage(set<WebPage*>,set<WebPage*>);
		set<WebPage*> unionWebPage(set<WebPage*>, set<WebPage*>);
		set<WebPage*> get_incoming(string);
		set<WebPage*> get_outgoing(string);
		void print(ofstream&, string);

	private:
		vector <WebPage*> webPages;

};
#endif