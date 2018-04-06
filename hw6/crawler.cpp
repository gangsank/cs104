#include "WebPage.h"
#include "setutility.h"
#include <sstream>
#include <stack>

using namespace std;

void dfs (vector<WebPage*>& webPages, ofstream& output)
{
	stack<WebPage*> mystack;
	vector<WebPage*> webs = webPages;

	for (unsigned int i=0; i<webPages.size(); i++)
	{
		webPages[i]->set_unvisited();
	}

	while(!webs.empty())
	{
		WebPage* temp = webs.back();
		
		webs.pop_back();
		mystack.push(temp);
	}

	while(!mystack.empty())
	{
		WebPage* u = mystack.top();

		if (u->get_visited()==false)
		{
			output << u->get_filename() << endl;
			u->set_visited();
			set<WebPage*> outlinks = u->get_outLinks();
			set<WebPage*>::iterator it;

			for (it = outlinks.begin(); it != outlinks.end(); ++it)
			{
				if((*it)->get_visited()==false)
				{
					webPages.push_back(*it);
					(*it)->parse(webPages);
					mystack.push(*it);
				}
			}
		}
		else
		{
			mystack.pop();
		}
	}

	//Deallocating all memories
	for (unsigned int i=0; i<webPages.size(); i++)
	{
		delete webPages[i];
	}
}

int main(int argc, char* argv[])
{
	string index_;
	string output_;

	ifstream config;

	//if user does not provide a config file
	if (argc == 1)
	{
		config.open("config.txt");
	}

	else if (argc > 2)
	{
		return 1;
	}

	//opening the user provided config file
	else
	{
		config.open(argv[1]);
	}

	string buffer;

	size_t indexfound;
	size_t outputfound;
	size_t commentfound;

	//Extracting all necessary information from config
	while(getline(config,buffer))
	{
		stringstream ss;

		if(buffer=="")
		{
			continue;
		}

		else
		{
			commentfound = buffer.find("#");

			//Ignoring everthing after a '#'
			if(commentfound != string::npos)
			{
				buffer = buffer.substr(0,commentfound);
			}

			//Since order does not matter
			indexfound = buffer.find("INDEX_FILE");
			outputfound = buffer.find("OUTPUT_FILE");

			//found index
			if(indexfound != string::npos)
			{
				//cutting out "INDEX_FILE"
				buffer = buffer.substr(indexfound+10);

				//assigning the filepath
				indexfound = buffer.find("=");
				buffer = buffer.substr(indexfound+1);

				ss << buffer;
				ss >> index_; 
				ss.clear();
			}

			//found output
			else if (outputfound != string::npos)
			{
				//cutting out "OUTPUT_FILE"
				buffer = buffer.substr(outputfound+11);
				//assigning the filepath 
				outputfound = buffer.find('=');
				buffer = buffer.substr(outputfound+1);

				ss << buffer;
				ss >> output_;
				ss.clear();
			}

			buffer.clear();
		}
	}

	//Opening the given files from config
	ifstream index (index_.c_str());
	ofstream output (output_.c_str());

	string buff;
	vector<WebPage*> webPages;

	//Extract the names of the files from index file
	//Then, add all files to a vector of WebPage*
	while(getline(index,buff))
	{
		if(buff=="")
		{
			continue;
		}
		WebPage* temp = new WebPage(buff);	
		webPages.push_back(temp);
	}

	//Parsing the files in config
	for (unsigned int i=0; i<webPages.size(); i++)
	{
		webPages[i]->parse(webPages);
	}

	//Doing dfs
	dfs(webPages, output);	
}
