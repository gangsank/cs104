#include "WebPage.h"
#include "Manager.h"
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	ifstream index (argv[1]);
	ifstream query (argv[2]);
	ofstream output (argv[3]);

	string buffer;
	vector<WebPage*> webPages;

	//Extract the names of the files from index file
	//Then, add all files to a vector of WebPage*
	while(getline(index,buffer))
	{
		if(buffer=="")
		{
			continue;
		}
		WebPage* temp = new WebPage(buffer);		
		webPages.push_back(temp);
	}

	//Parse each file in the vector
	for (unsigned int i=0; i<webPages.size(); i++)
	{
		webPages[i]->parse(webPages);
	}

	string command;

	Manager manager(webPages);

	//Executing query
	while (getline(query, command))
	{
		string target;
		string page;
		stringstream ss;
		ss << command;
		command.clear();
		ss >> command;

		//AND (Intersection of pages)
		if (command == "AND")
		{
			set<WebPage*> result1;
			set<WebPage*> result2;

			bool targetexists = false;

			if(ss>>target)
			{
				targetexists = true;
				result1 = manager.do_search(target); 
			}

			else
			{
				result1 = manager.do_search("AND");
			}

			if(targetexists)
			{
				while (ss>>target)
				{
					result2 = manager.do_search(target);
					result1 = manager.intersectWebPage(result1,result2);
				}
			}
			
			int size = result1.size();
			output << size << endl;

			set<WebPage*>::iterator it;

			for (it = result1.begin(); it != result1.end(); ++it)
			{
				output << (*it)->get_filename() << endl;
			}

		}

		//OR (Union of pages)
		else if (command == "OR")
		{
			set<WebPage*> result1;
			set<WebPage*> result2;
			int count = 0;

			bool targetexists = false;

			if(ss>>target)
			{
				targetexists = true;
				result1 = manager.do_search(target); 
				count++;
			}

			else
			{
				result1 = manager.do_search("OR");
			}

			if(targetexists)
			{
				while (ss>>target)
				{
					result2 = manager.do_search(target);
					result1 = manager.unionWebPage(result1,result2);
				}
			}

			int size = result1.size();
			output << size << endl;

			set<WebPage*>::iterator it;
			
			for (it = result1.begin(); it != result1.end(); ++it)
			{
				output << (*it)->get_filename() << endl;
			}

		}

		//PRINT page
		else if (command == "PRINT")
		{
			int count = 0;
			
			while(ss>>page)
			{
				count++;
			}

			if(count!=1)
			{
				output << "Invalid query" << endl;
			}

			else
			{	output << page << endl;
				manager.print(output,page);
			}
			
		}	

		//INCOMING page
		else if (command == "INCOMING")
		{
			int count = 0;
			set<WebPage*> result;

			while (ss>>page)
			{
				count++;
			}

			if(count!=1)
			{
				output << "Invalid query" << endl;
			}

			else
			{
				result = manager.get_incoming(page);
				int size = result.size();
				output << size << endl;

				set<WebPage*>::iterator it;
				for (it = result.begin(); it != result.end(); ++it)
				{
					output << (*it)->get_filename() << endl;
				}
			}
		}

		//OUTGOING page
		else if (command == "OUTGOING")
		{
			int count = 0;
			set<WebPage*> result;

			while(ss>>page)
			{
				count++;
			}

			if(count!=1)
			{
				output << "Invalid query" << endl;
			}

			else
			{
				result = manager.get_outgoing(page);

				int size = result.size();
				output << size << endl;

				set<WebPage*>:: iterator it;
				for(it = result.begin(); it!= result.end(); ++it)
				{
					output << (*it)->get_filename() << endl;
				}
			}
		}

		//Case for single word
		else
		{
			int count = 0;
			set<WebPage*> result;
			
			while (ss>>target)
			{
				count++;
			}

			if (count>0)
			{
				output << "Invalid query" << endl;
			}

			else
			{
				result = manager.do_search(command);

				int size = result.size();
				output << size << endl;

				set<WebPage*>:: iterator it;
				for(it = result.begin(); it!= result.end(); ++it)
				{
					output << (*it)->get_filename() << endl;
				}
			}
		}
		output << endl;
	}

	//Delete allocated memories
	for (unsigned int i=0; i<webPages.size(); i++)
	{	
		set<WebPage*> links;
		links = webPages[i]->get_outLinks();
		set<WebPage*>:: iterator it;

		for(it=links.begin(); it != links.end(); ++it)
		{
			if ((*it)->get_raw() == "")
			{
				delete *it;
			}
		}
	}

	for (unsigned int i=0; i<webPages.size(); i++)
	{
		delete webPages[i];
	}
}