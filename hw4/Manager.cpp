#include "Manager.h"

Manager::Manager()
{

}

Manager::Manager(vector<WebPage*> webs) : webPages(webs)
{

}

set<WebPage*> Manager::do_search(string word)
{
	set<WebPage*> result;
	string newword="";
	for (unsigned int i=0; i<word.size(); i++)
	{
		newword += tolower(word[i]);
	}

	for (unsigned int i=0; i<webPages.size(); i++)
	{
		bool found = false;
		set<string> content = webPages[i]->get_content();
		set<string> real;

		set<string>::iterator it1;

		for (it1 = content.begin(); it1 != content.end(); ++it1)
		{
			string lower="";
			for(unsigned int j=0; j<(*it1).size(); j++)
			{
				lower += tolower((*it1)[j]);
			}

			
			real.insert(lower);
		}

		set<string>::iterator it2;

		for (it2 = real.begin(); it2 != real.end(); ++it2)
		{
			if (*it2 == newword)
			{
				found = true;
				break;
			}
		}

		if(found)
		{
			result.insert(webPages[i]);
		}
	}

	return result;
}

set<WebPage*> Manager::intersectWebPage(set<WebPage*> result1, set<WebPage*> result2)
{
	set<WebPage*>::iterator it1;
	set<WebPage*>::iterator it2;
	set<WebPage*> intersect;

	for (it1 = result1.begin(); it1 != result1.end(); ++it1)
	{
		for (it2 = result2.begin(); it2 != result2.end(); ++it2)
		{
			if (*it1==*it2)
			{
				intersect.insert(*it1);
			}
		}
	}

	return intersect;
}

set<WebPage*> Manager::unionWebPage(set<WebPage*> result1, set<WebPage*> result2)
{
	set<WebPage*>::iterator it1;
	set<WebPage*>::iterator it2;
	set<WebPage*> uni;

	for (it1 = result1.begin(); it1 != result1.end(); ++it1)
	{
		uni.insert(*it1);
	}	
	
	for (it2 = result2.begin(); it2 != result2.end(); ++it2)
	{
		uni.insert(*it2);
	}		
	
	return uni;
}

set<WebPage*> Manager::get_incoming(string file)
{
	set<WebPage*> result;

	for (unsigned int i=0; i<webPages.size(); i++)
	{
		if(webPages[i]->get_filename()==file)
		{
			result = webPages[i]->get_inLinks();
		}
	}

	return result;
}

set<WebPage*> Manager::get_outgoing(string file)
{
	set<WebPage*> result;

	for (unsigned int i=0; i<webPages.size(); i++)
	{
		if(webPages[i]->get_filename()==file)
		{
			result = webPages[i]->get_outLinks();
		}
	}

	return result;
}

void Manager::print(ofstream &output, string file)
{
	for (unsigned int i=0; i<webPages.size(); i++)
	{
		if(webPages[i]->get_filename()==file)
		{
			webPages[i]->print_content(output);
			break;
		}
	}
}

