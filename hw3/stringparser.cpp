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
	int len = (int)rhs.length();

	for (int i=0; i<len; i++)
	{
		sub = rhs.substr(i,len-i);

		int found = (int)lhs.find(sub);

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
	//If a plus or a minus is in front of the parenthesis, stop.
	if(s[0]=='+' || s[0]=='-')
	{
		return "";
	}

	bool plus = false;
	bool minus = false;
	int minuscount = 0;

	for (unsigned int i=0; i<s.length(); i++)
	{
		if (s[i]=='+')
		{
			plus = true;
		}

		else if (s[i]=='-')
		{
			minus = true;
			minuscount++;
		}
	}

	//If there is more than one minus operation, stop.
	if (minuscount > 1)
	{
		return "";
	}

	//If a plus and a minus are in a parenthesis together, stop.
	if (plus && minus)
	{
		return "";
	}

	StackStr stack;
	char oper;

	//Compute
	for (unsigned int i=0; i<s.length(); i++)
	{
		if((s[i] >= 'a' && s[i] <= 'z'))
        {
        	string temp;
        	temp += s[i];
        	int curr = i+1;

        	//Extracting a string
        	while (curr<(int)s.length() && (s[curr] >= 'a' 
        		&& s[curr] <= 'z'))
        	{
        		temp += s[curr];
        		curr++;
        	}

        	int temp1 = i-1;

        	//Do the '<' or '>' in front of the string
        	while ((s[temp1]=='<' || s[temp1]== '>')&&
        			temp1>=0)
        	{
        		deletion(s[temp1],temp);
        		temp1--;
        	}
       		i = curr;
        	stack.push(temp);
        }
 
 		//If the stack has two operands and the char has
 		//an operation, do the computation.
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

        //When operation is a plus
        if(s[i]=='+')
        {
        	oper = s[i];
        }

        //When operation is a minus
        else if (s[i]=='-')
        {
        	oper = s[i];
        }
    }
	
	//Return the top of this stack back to the original stack.
	string result = stack.top();
	stack.pop();

	return result;
}

string Eval(string s)
{
    StackStr stack;

    for(int i = 0; i < (int)s.length(); i++)
    {
        // If scanned a string, add to the stack.
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

        //If a blank space is scanned, skip.
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

            //Extracting everything in the parenthesis.
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

            //Push the computation result to the stack.
            stack.push(middle);
        }
         
        //If an operator is scanned
        else
        {
            string p(1,s[i]);
            stack.push(p);
        }
    }

    string result = stack.top();
    stack.pop();

    //Checking for extra operations.
    while (stack.top()==">" || stack.top()=="<")
    {
    	char op = (stack.top())[0];
    	deletion(op,result);
    	stack.pop();
    }

    //If stack is not empty after doing the computations,stop.
    if(!stack.empty())
    {
    	return"";
    }
	
	//If everything is correct, return the result.
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

	//Reading each line of the input
	while(getline(ifile,buffer))
	{
		bool malformed = false;

		//If the line is empty, stop.
		if(buffer=="")
		{
			ofile << "Malformed" << endl;
			continue;
		}
	
		//if the line contains a capital letter, stop.
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

			//If Malformed
			if(result=="")
			{
				ofile << "Malformed" << endl;
			}
			//If string expression is correct
			else
			{
			ofile << result << endl;
			}
		}
	}	
}