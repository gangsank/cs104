#include "functor.h"

bool NumStrComp::operator()(const string& lhs, const string& rhs)
{
	if(lhs==rhs)
	{
		return false;
	}

	int lhssum=0;
	int rhssum=0;

	bool result;

	//adding up the left side
	for (unsigned int i=0; i<lhs.size(); i++)
	{
		if (lhs[i]=='0')
		{
			continue;
		}

		else if (lhs[i]=='1')
		{
			lhssum+=1;
		}

		else if (lhs[i]=='2')
		{
			lhssum+=2;
		}

		else if (lhs[i]=='3')
		{
			lhssum+=3;
		}

		else if (lhs[i]=='4')
		{
			lhssum+=4;
		}

		else if (lhs[i]=='5')
		{
			lhssum+=5;
		}

		else if (lhs[i]=='6')
		{
			lhssum+=6;
		}

		else if (lhs[i]=='7')
		{
			lhssum+=7;
		}

		else if (lhs[i]=='8')
		{
			lhssum+=8;
		}

		else if (lhs[i]=='9')
		{
			lhssum+=9;
		}

		else if (lhs[i]=='a'||lhs[i]=='A')
		{
			lhssum+=10;
		}

		else if (lhs[i]=='b'||lhs[i]=='B')
		{
			lhssum+=11;
		}

		else if (lhs[i]=='c'||lhs[i]=='C')
		{
			lhssum+=12;
		}

		else if (lhs[i]=='d'||lhs[i]=='D')
		{
			lhssum+=13;
		}

		else if (lhs[i]=='e'||lhs[i]=='E')
		{
			lhssum+=14;
		}

		else if (lhs[i]=='f'||lhs[i]=='F')
		{
			lhssum+=15;
		}

		else if (lhs[i]=='g'||lhs[i]=='G')
		{
			lhssum+=16;
		}

		else if (lhs[i]=='h'||lhs[i]=='H')
		{
			lhssum+=17;
		}

		else if (lhs[i]=='i'||lhs[i]=='I')
		{
			lhssum+=18;
		}

		else if (lhs[i]=='j'||lhs[i]=='J')
		{
			lhssum+=19;
		}

		else if (lhs[i]=='k'||lhs[i]=='K')
		{
			lhssum+=20;
		}

		else if (lhs[i]=='l'||lhs[i]=='L')
		{
			lhssum+=21;
		}

		else if (lhs[i]=='m'||lhs[i]=='M')
		{
			lhssum+=22;
		}

		else if (lhs[i]=='n'||lhs[i]=='N')
		{
			lhssum+=23;
		}

		else if (lhs[i]=='o'||lhs[i]=='O')
		{
			lhssum+=24;
		}

		else if (lhs[i]=='p'||lhs[i]=='P')
		{
			lhssum+=25;
		}

		else if (lhs[i]=='q'||lhs[i]=='Q')
		{
			lhssum+=26;
		}

		else if (lhs[i]=='r'||lhs[i]=='R')
		{
			lhssum+=27;
		}

		else if (lhs[i]=='s'||lhs[i]=='S')
		{
			lhssum+=28;
		}

		else if (lhs[i]=='t'||lhs[i]=='T')
		{
			lhssum+=29;
		}

		else if (lhs[i]=='u'||lhs[i]=='U')
		{
			lhssum+=30;
		}

		else if (lhs[i]=='v'||lhs[i]=='V')
		{
			lhssum+=31;
		}

		else if (lhs[i]=='w'||lhs[i]=='W')
		{
			lhssum+=32;
		}

		else if (lhs[i]=='x'||lhs[i]=='X')
		{
			lhssum+=33;
		}

		else if (lhs[i]=='y'||lhs[i]=='Y')
		{
			lhssum+=34;
		}

		else if (lhs[i]=='z'||lhs[i]=='Z')
		{
			lhssum+=35;
		}

		else
		{
			continue;
		}
	}

	//adding up the right side
	for (unsigned int i=0; i<rhs.size(); i++)
	{
		if (rhs[i]=='0')
		{
			continue;
		}

		else if (rhs[i]=='1')
		{
			rhssum+=1;
		}

		else if (rhs[i]=='2')
		{
			rhssum+=2;
		}

		else if (rhs[i]=='3')
		{
			rhssum+=3;
		}

		else if (rhs[i]=='4')
		{
			rhssum+=4;
		}

		else if (rhs[i]=='5')
		{
			rhssum+=5;
		}

		else if (rhs[i]=='6')
		{
			rhssum+=6;
		}

		else if (rhs[i]=='7')
		{
			rhssum+=7;
		}

		else if (rhs[i]=='8')
		{
			rhssum+=8;
		}

		else if (rhs[i]=='9')
		{
			rhssum+=9;
		}

		else if (rhs[i]=='a'||rhs[i]=='A')
		{
			rhssum+=10;
		}

		else if (rhs[i]=='b'||rhs[i]=='B')
		{
			rhssum+=11;
		}

		else if (rhs[i]=='c'||rhs[i]=='C')
		{
			rhssum+=12;
		}

		else if (rhs[i]=='d'||rhs[i]=='D')
		{
			rhssum+=13;
		}

		else if (rhs[i]=='e'||rhs[i]=='E')
		{
			rhssum+=14;
		}

		else if (rhs[i]=='f'||rhs[i]=='F')
		{
			rhssum+=15;
		}

		else if (rhs[i]=='g'||rhs[i]=='G')
		{
			rhssum+=16;
		}

		else if (rhs[i]=='h'||rhs[i]=='H')
		{
			rhssum+=17;
		}

		else if (rhs[i]=='i'||rhs[i]=='I')
		{
			rhssum+=18;
		}

		else if (rhs[i]=='j'||rhs[i]=='J')
		{
			rhssum+=19;
		}

		else if (rhs[i]=='k'||rhs[i]=='K')
		{
			rhssum+=20;
		}

		else if (rhs[i]=='l'||rhs[i]=='L')
		{
			rhssum+=21;
		}

		else if (rhs[i]=='m'||rhs[i]=='M')
		{
			rhssum+=22;
		}

		else if (rhs[i]=='n'||rhs[i]=='N')
		{
			rhssum+=23;
		}

		else if (rhs[i]=='o'||rhs[i]=='O')
		{
			rhssum+=24;
		}

		else if (rhs[i]=='p'||rhs[i]=='P')
		{
			rhssum+=25;
		}

		else if (rhs[i]=='q'||rhs[i]=='Q')
		{
			rhssum+=26;
		}

		else if (rhs[i]=='r'||rhs[i]=='R')
		{
			rhssum+=27;
		}

		else if (rhs[i]=='s'||rhs[i]=='S')
		{
			rhssum+=28;
		}

		else if (rhs[i]=='t'||rhs[i]=='T')
		{
			rhssum+=29;
		}

		else if (rhs[i]=='u'||rhs[i]=='U')
		{
			rhssum+=30;
		}

		else if (rhs[i]=='v'||rhs[i]=='V')
		{
			rhssum+=31;
		}

		else if (rhs[i]=='w'||rhs[i]=='W')
		{
			rhssum+=32;
		}

		else if (rhs[i]=='x'||rhs[i]=='X')
		{
			rhssum+=33;
		}

		else if (rhs[i]=='y'||rhs[i]=='Y')
		{
			rhssum+=34;
		}

		else if (rhs[i]=='z'||rhs[i]=='Z')
		{
			rhssum+=35;
		}

		else
		{
			continue;
		}
	}

	//Gauging the result
	if (lhssum < rhssum)
	{
		result = true;
	}

	else if (lhssum == rhssum)
	{
		if(lhs<rhs)
		{
			result = true;
		}

		else
		{
			result = false;
		}
	}

	else
	{
		result = false;
	}

	return result;
}