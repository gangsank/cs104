#include "WebPage.h"

//Empty Constructor
WebPage::WebPage()
{

}

//Constructor with filename initializer
WebPage::WebPage(string name) : filename(name)
{
	ifstream ifile (filename.c_str());
	string buffer;
	while(getline(ifile,buffer))
	{
		raw+=buffer;
	}
}

//Destructor
WebPage::~WebPage()
{

}

string WebPage::get_filename()
{
	return filename;
}

string WebPage::get_raw()
{
	return raw;
}

//Print the parsed contents of a webpage
void WebPage::print_content(ofstream &output)
{
	ifstream ifile (filename.c_str());
	string buffer;

	while(getline(ifile,buffer))
	{
		int i=0;

		while (i <(int)buffer.size())
		{
			if(buffer[i]=='(')
			{
				while (buffer[i] != ')')
				{
					i++;
				}
				i++;
			}
			output << buffer[i];
			i++;
		}
		output << endl;
	}
}
		
//Parse the raw contents of a webpage
void WebPage::parse(const vector<WebPage*> webPages)
{
	string word;
	string link;

	for (unsigned int i = 0; i <= raw.length(); i++)
	{
		
    	if (isalnum(raw[i]))
    	{
    		word+=raw[i];
    	}

    	else if (!isalnum(raw[i]) && raw[i] == '[')
    	{
    		word+=raw[i];
    	}

    	else if(!isalnum(raw[i]) && raw[i] !=']' && word !="")
    	{
    		content.insert(word);
    		word.clear();
    	}

    	else if(!isalnum(raw[i]) && raw[i] == ']')
    	{
    		word+=raw[i];
    		content.insert(word);
    		word.clear();
    	}
    	else if (i==raw.length())
    	{
    		content.insert(word);
    		word.clear();
    	}
    	
    	else if (raw[i] == '(')
    	{
      		while(raw[i] != ')')
      		{
        		i++;
        		link += raw[i];
      		}
      		link.erase(link.end()-1);
			
			for (unsigned int j=0; j<webPages.size(); j++)
			{
				if(webPages[j]->get_filename()==link)
				{
					WebPage* temp = webPages[j];
					temp->add_inLink(this);
					this->add_outLink(temp);
				}
			}
			
			link.clear();
		}
	}
}

set<WebPage*> WebPage::get_inLinks()
{
	return inLinks;
}

set<WebPage*> WebPage::get_outLinks()
{
	return outLinks;
}

void WebPage::add_inLink (WebPage* web)
{
	inLinks.insert(web);
}

void WebPage::add_outLink (WebPage* web)
{
	outLinks.insert(web);
}

set<string> WebPage::get_content()
{
	return content;
}

//for debugging
void WebPage::print_parsed()
{
	set<string>::iterator it;

	for (it = content.begin(); it != content.end (); ++it)
	{
		cout << *it << endl;
	}
}