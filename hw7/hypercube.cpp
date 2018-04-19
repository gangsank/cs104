#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string> 
#include <cmath>  
#include <queue>

using namespace std;

class Node
{
	public:
		Node();
		~Node();
		string get_bits() const;
		int get_g() const;
		int get_f() const;
		int get_h() const;
		int get_val() const;
		bool get_visited() const;
		void set_g(int temp1);
		void set_h(int temp2);
		void set_f(int temp3);
		void set_bits(string s);
		void set_visited(bool v);
		void set_val(int v);

	private:
		string bits;
		int val;
		int g;
		int f;
		int h;
		bool visited;
};

Node::Node()
{

}

Node::~Node()
{

}

string Node::get_bits() const
{
	return bits;
}

int Node::get_g() const
{
	return g;
}

int Node::get_f() const
{
	return f;
}

int Node::get_h() const
{
	return h;
}

bool Node::get_visited() const
{
	return visited;
}

int Node::get_val() const
{
	return val;
}

void Node::set_f(int temp1)
{
	f= temp1;
}

void Node::set_h(int temp2)
{
	h = temp2;
}

void Node::set_g(int temp3)
{
	g = temp3;
}

void Node::set_visited(bool visited1)
{
	visited = visited1;
}

void Node::set_bits(string s)
{
	bits = s;
}

void Node::set_val(int v1)
{
	val = v1;
}

struct Compare
{
	bool operator() (const Node* lhs, const Node* rhs)
	{
		if (lhs->get_f() == rhs->get_f() && lhs->get_h() == rhs->get_h())
		{
			if (lhs->get_val() > rhs->get_val())
			{
				return true;
			}

			else
			{
				return false;
			}
		}

		else if (lhs->get_f() == rhs->get_f())
		{
			if(lhs->get_h() > rhs->get_h())
			{
				return true;
			}

			else
			{
				return false;
			}
		}

		else
		{
			if (lhs->get_f() > rhs->get_f())
			{
				return true;
			}

			else
			{
				return false;
			}
		}
	}
};

int main(int argc, char* argv[])
{		
	int startNode;
	string startBit;
	int zeroes;
	int original;
	int ones = 0;
	int length;
	int expansion = 0;
	int nocount = 0;
	int distance = 1;
	int mid;
	bool finish = false;
	bool pathExist = true;

	Node* start = new Node();
	string line;
	string t;
	vector<Node*> cube;
	vector<Node*> result;

	priority_queue<Node*, vector<Node*>, Compare> path;

	startBit = argv[1];
	startNode = atoi(argv[1]);
	original = startNode;
	t = argv[1];
	length = t.length();
	zeroes = length;

	//Finding the number of 1s
	while(original > 0)
	{
		ones += original%10;
		original /= 10;
	}

	//Finding the number of 0s
	zeroes -= ones;

	start->set_val(startNode);
	start->set_visited(true);
	start->set_bits(argv[1]);
	start->set_g(0);
	start->set_h(zeroes);

	path.push(start);
	result.push_back(start);

	ifstream ifile(argv[2]);

if(ifile)
{
	getline(ifile, line);

	//Inserting the permissible nodes
	while (getline(ifile, line))
	{
		Node* node = new Node();
		node->set_val(stoi(line));
		node->set_bits(line);
		node->set_visited(false);

		if (node->get_bits() == startBit)
		{
			node->set_visited(true);
		}

		ones = 0;
		original = node->get_val();

		while (original > 0)
		{
			ones += original%10;
			original /= 10;
		}

		node->set_h(length-ones);
		node->set_g(abs(zeroes-(node->get_h())));
		node->set_f((node->get_h())+(node->get_g()));
		cube.push_back(node);
	}
}

	while (!path.empty())
	{
		mid = 0;

		for (size_t i=0; i<cube.size(); i++)
		{
			if (cube[i]->get_visited()==false)
			{
				if(cube[i]->get_g() == distance)
				{
					int comp = 0;

					for (size_t j=0; j<cube[i]->get_bits().size(); j++)
					{
						//if the node differs by one bit
						if (cube[i]->get_bits()[j] != result[result.size()-1]->get_bits()[j])
						{
							comp++;
						}
					}

					if (comp == 1)
					{
						cube[i]->set_visited(true);
						path.push(cube[i]);
						mid++;
					}
				}
			}
		}

		if (mid == 0)
		{
			path.pop();
			nocount++;
			expansion++;
			distance--;

			if (path.top()->get_g() == distance)
			{
				distance++;
			}

			else
			{
				distance--;
			}

			if(path.empty())
			{
				finish = true;
			}

			else 
			{
				if(result[result.size()-1]->get_bits() != path.top()->get_bits())
				{
					if(result.back()->get_h() == path.top()->get_h())
					{
						result.pop_back();
					}

					result.push_back(path.top());
				}
			}
		}

		else
		{
			distance++;
		}

		if(!finish)
		{
			if(result[result.size()-1]->get_bits() != path.top()->get_bits())
			{
				if(result.back()->get_h() == path.top()->get_h())
				{
					result.pop_back();
				}

				result.push_back(path.top());
				expansion++;
			}
		}

		else if (result[result.size()-1]->get_h() == 0)
		{
			while(!path.empty())
			{
				path.pop();
			}
		}

		if (result[result.size()-1]->get_h() == 0)
		{
			while(!path.empty())
			{
				path.pop();
			}
		}
	}

	if (result[result.size()-1]->get_h() != 0)
	{
		pathExist = false;
	}

	//Backtrace
	if (!pathExist)
	{
		cout << "No transformation" << endl;
		cout << "expansions = " << nocount << endl;
	}

	else
	{
		for (size_t i=0; i<result.size(); i++)
		{
			cout << result[i]->get_bits() << endl;
		}

		cout << "expansions = " << expansion << endl;
	}

	//Deallocate all memories
	delete start;

	for (size_t i=0; i<cube.size(); i++)
		{
			delete cube[i];
		}

	return 0;
}
