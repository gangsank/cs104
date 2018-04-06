#include "WebPage.h"
#include "Manager.h"
#include "setutility.h"
#include <sstream>
#include <queue>
#include <stack>
using namespace std;

set<WebPage*> candidates (set<WebPage*>& original)
{
	set<WebPage*> candidates;
	set<WebPage*>::iterator it;

	for (it = original.begin(); it != original.end(); ++it)
	{
		candidates.insert(*it);

		set<WebPage*> inLinks;
		set<WebPage*> outLinks;

		inLinks = (*it)->get_inLinks();
		outLinks = (*it)->get_outLinks();

		set<WebPage*>::iterator in;
		set<WebPage*>::iterator out;

		for (in = inLinks.begin(); in != inLinks.end(); ++in)
		{
			candidates.insert(*in);
		}

		for (out = outLinks.begin(); out != outLinks.end(); ++out)
		{
			candidates.insert(*out);
		}
	}

	return candidates;
}

double p(WebPage* web, double probability, int size)
{
	double prob;

	set<WebPage*> incoming = web->get_inLinks();
	set<WebPage*>::iterator it;

	//Computation for the ranks
	for(it = incoming.begin(); it != incoming.end(); ++it)
	{
		int num = (*it)->get_outLinksSize();
		prob+=(1-probability)*(*it)->get_rank()/num;
	}

	prob += (probability/size);

	return prob;
}

map<double,WebPage*> PageRank (set<WebPage*>& candidates, double probability, int step)
{
	map<double, WebPage*> ranks;
	set<WebPage*>::iterator it;
	int size = (int)candidates.size();

	//Adding a self-loop to each node and setting the initial rank to 1/n
	for (it = candidates.begin(); it != candidates.end(); ++it)
	{
		(*it)->add_inLink(*it);
		(*it)->add_outLink(*it);
		(*it)->set_rank(1.0/size);
	}

	queue<double> oldranks;

	//Computing the rank
	for (int i=0; i<step; i++)
	{
		for (it = candidates.begin(); it != candidates.end(); ++it)
		{
			oldranks.push(p(*it, probability, size));
		}

		for (it = candidates.begin(); it != candidates.end(); ++it)
		{
			double r = oldranks.front();
			oldranks.pop();
			(*it)->set_rank(r);
		}
	}

	//sorting the pages by inserting into a map
	for (it = candidates.begin(); it != candidates.end(); ++it)
		{
			pair<double,WebPage*> ret;
			ret = make_pair((*it)->get_rank(), (*it));
			ranks.insert(ret);
		}

	return ranks;
}

int main(int argc, char* argv[])
{
	string index_;
	string output_;
	string query_;
	double probability;
	int stepnum;
	ifstream config;

	//if user does not provide a config file, default.
	if (argc == 1)
	{
		config.open("config.txt");
	}

	//error case
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
	size_t queryfound;
	size_t probabilityfound;
	size_t stepfound;
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
			queryfound = buffer.find("QUERY_FILE");
			probabilityfound = buffer.find("RESTART_PROBABILITY");
			stepfound = buffer.find("STEP_NUMBER");

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

			//found query
			else if (queryfound != string::npos)
			{
				//cutting out "QUERY_FILE"
				buffer = buffer.substr(queryfound+10);
				//assigning the filepath 
				queryfound = buffer.find('=');
				buffer = buffer.substr(queryfound+1);

				ss << buffer;
				ss >> query_;
				ss.clear();

			}

			//found probability
			else if (probabilityfound != string::npos)
			{
				//cutting out "RESTART_PROBABILITY"
				buffer = buffer.substr(probabilityfound+19);
				//assigning the filepath 
				probabilityfound = buffer.find('=');
				buffer = buffer.substr(probabilityfound+1);

				ss << buffer;
				ss >> probability;
				ss.clear();
			}

			//found number of steps
			else if (stepfound != string::npos)
			{
				//cutting out "STEP_NUMBER"
				buffer = buffer.substr(stepfound+11);
				//assigning the filepath 
				stepfound = buffer.find('=');
				buffer = buffer.substr(stepfound+1);

				ss << buffer;
				ss >> stepnum;
				ss.clear();
			}

			buffer.clear();
		}
	}

	//Opening the given files from config
	ifstream index (index_.c_str());
	ofstream output (output_.c_str());
	ifstream query (query_.c_str());

	string buff;
	vector<WebPage*> webPages;

	//Extract the names of the files from the index
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

		//AND (Intersection of webpages)
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
			
			set<WebPage*> cand = candidates(result1); 
			map<double,WebPage*> ranks = PageRank(cand, probability, stepnum);

			int size = (int)ranks.size();
			output << size << endl;

			map<double,WebPage*>::iterator it;

			stack<WebPage*> mystack;
			
			for (it=ranks.begin(); it != ranks.end(); ++it)
			{
				mystack.push(it->second);
			}
			
			while(!mystack.empty())
			{
				WebPage* temp = mystack.top();
				mystack.pop();
				output << temp->get_filename() << endl;
			}
			
		}

		//OR (Union of webpages)
		else if (command == "OR")
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

			set<WebPage*> cand = candidates(result1); 
			map<double,WebPage*> ranks = PageRank(cand, probability, stepnum);

			int size = (int)ranks.size();
			output << size << endl;

			map<double,WebPage*>::iterator it;

			stack<WebPage*> mystack;
			
			for (it=ranks.begin(); it != ranks.end(); ++it)
			{
				mystack.push(it->second);
			}
			
			while(!mystack.empty())
			{
				WebPage* temp = mystack.top();
				mystack.pop();
				output << temp->get_filename() << endl;
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

			if (count == 0)
			{
				set<WebPage*> result = manager.do_search(command);

				int size = result.size();
				output << size << endl;

				set<WebPage*>:: iterator it;
				for(it = result.begin(); it!= result.end(); ++it)
				{
					output << (*it)->get_filename() << endl;
				}
			}

			if(count>1)
			{
				output << "Invalid query" << endl;
			}

			else
			{	output << page << endl;
				manager.print(output,page);
			}
		}	

		//INCOMING page (d-(v))
		else if (command == "INCOMING")
		{
			int count = 0;
			set<WebPage*> result;

			while (ss>>page)
			{
				count++;
			}

			if (count == 0)
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

			else if(count>1)
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

		//OUTGOING page (d+(v))
		else if (command == "OUTGOING")
		{
			int count = 0;
			set<WebPage*> result;

			while(ss>>page)
			{
				count++;
			}

		 	if (count == 0)
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

			else if(count > 1)
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

			if (count>1)
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

	index.close();
	output.close();
	query.close();
}