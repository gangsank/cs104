#include <iostream>
#include <string>
#include <fstream>
#include "stackstr.h"

using namespace std;

string operator+ (const string& lhs, const string& rhs)
{	
	string temp;
	temp.append(lhs);
	temp.append(rhs);
	return temp;
}

string operator- (string lhs, string rhs)
{
	string sub;
	int len = rhs.length();

	for (int i=0; i<len; i++)
	{
		sub = rhs.substr(i,len-i);

		int found = lhs.find(sub);

		if(found>=0)
		{
			lhs.erase(found,sub.length());
			return lhs;
		}
	}

	return lhs;
}

void deletion (char operation, string& s)
{
	if (operation == '<')
	{
		if (s.length()==1)
		{
			return;
		}

	s.erase(s.length()-1);
	}

	else if (operation == '>')
	{
		if (s.length()==1)
		{
			return;
		}

	s.erase(s.begin());
	}
}

string Computation (string s)
{

	if(s[0]=='+' || s[0]=='-')
	{
		return "";
	}

	bool plus = false;
	bool minus = false;

	for (unsigned int i=0; i<s.length(); i++)
	{
		if (s[i]=='+')
		{
			plus = true;
		}

		else if (s[i]=='-')
		{
			minus = true;
		}
	}

	if (plus && minus)
	{
		return "";
	}

	StackStr stack;
	char oper;

	for (unsigned int i=0; i<s.length(); i++)
	{
		if((s[i] >= 'a' && s[i] <= 'z'))
        {
        	string temp;
        	temp += s[i];
        	int curr = i+1;

        	while (curr<(int)s.length() && (s[curr] >= 'a' 
        		&& s[curr] <= 'z'))
        	{
        		temp += s[curr];
        		curr++;
        	}

        	int temp1 = i-1;

        	while ((s[temp1]=='<' || s[temp1]== '>')&&
        			temp1>=0)
        	{
        		deletion(s[temp1],temp);
        		temp1--;
        	}
       		i = curr;
        	stack.push(temp);
        }
 
        if (stack.size()==2&&oper)
        {
        	string second = stack.top();
        	stack.pop();
        	string first = stack.top();
        	stack.pop();
        	string third;
        	if(oper=='+')
        	{
        		third = first+second;
        	}
        	else if (oper=='-')
        	{
        		third = first-second;
        	}
        	stack.push(third);
        }

        if(s[i]=='+')
        {
        	oper = s[i];
        }

        else if (s[i]=='-')
        {
        	oper = s[i];
        }
    }
	
	string result = stack.top();
	stack.pop();

	return result;
}

string Eval(string s)
{
    StackStr stack;

    for(int i = 0; i < (int)s.length(); i++)
    {
        // If the scanned string is an operand, add it to output string.
     	if((s[i] >= 'a' && s[i] <= 'z'))
        {
        	string temp;
        	temp += s[i];
        	int curr = i+1;

        	while (curr<(int)s.length() && (s[curr] >= 'a' 
        		&& s[curr] <= 'z'))
        	{
        		temp += s[curr];
        		curr++;
        	}
        	i = curr-1;

        	for (unsigned int j=0; j<temp.length(); j++)
        	{
        		if (temp[j]==' ')
        		{
        			return "";
        		}
        	}
        	stack.push(temp);
        }

       	else if (s[i]==' ')
       	{
       		continue;
       	}
 
        // If scanned an opening parenthesis, push it to the stack.
        else if(s[i] == '(')
        {
        	string p (1,'(');
        	stack.push(p);
       	}

        //If scanned a closing parenthesis, 
        //pop from the stack until an opening parenthesis is encountered.
        //Then, do the computation.
        else if(s[i] == ')')
        {
        	string c;
        	StackStr tempstack;

            while((!stack.empty())&& stack.top() != "(")
            {
               c = stack.top();
               stack.pop();
               tempstack.push(c);
            }

            if(stack.top() == "(")
            {
                stack.pop();
            }

            string a;
            while(!tempstack.empty())
            {
            	a += tempstack.top();
            	tempstack.pop();
            }

            string middle = Computation(a);

            if(middle=="")
            {
            	return "";
            }

            stack.push(middle);
        }
         
        //If an operator is scanned
        else
        {
            string p(1,s[i]);
            stack.push(p);
        }
    }

    //Print out the result
    //If the stack contains something else, terminate.
    string result = stack.top();
    stack.pop();

    while (stack.top()==">" || stack.top()=="<")
    {
    	char op = (stack.top())[0];
    	deletion(op,result);
    	stack.pop();
    }

    if(!stack.empty())
    {
    	return"";
    }
	
    return result;
} 


int main (int argc, char* argv[])
{
	ifstream ifile(argv[1]);
	ofstream ofile(argv[2]);

	if(argc < 3)
	{
		cout << "Not enough files" << endl;
		return 0;
	}

	if(ifile.fail())
	{
		cout << "Not valid inputs" << endl;
		return 0;
	}

	string buffer;

	while(getline(ifile,buffer))
	{
		bool malformed = false;
		if(buffer=="")
		{
			ofile << "Malformed" << endl;
			continue;
		}
	
		for (int i=0; i<(int)buffer.length(); i++)
		{
			if(((buffer[i]>='A'&&buffer[i]<='Z')))
			{
				ofile << "Malformed" << endl;
				malformed = true;
				break;
			}
		}

		if(!malformed)
		{
			string result = Eval(buffer);
			if(result=="")
			{
				ofile << "Malformed" << endl;
			}
			else
			{
			ofile << result << endl;
			}
		}
	}	
}