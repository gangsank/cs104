#include "LengthMismatch.h"

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

vector<pair<int,int> > assignPlates(vector<int> turkeys,vector<int> potatoes) 
{
	int turkeysize = (int)turkeys.size();
	int potatosize = (int)potatoes.size();

    if(turkeysize!=potatosize)
    {
     	throw LengthMismatch(turkeysize,potatosize);
    }

    vector<pair<int,int> > plates;

    sort(turkeys.begin(), turkeys.end());
    sort(potatoes.begin(), potatoes.end());

    vector<int> reversedPotatoes;
    
    for (int i=potatosize-1; i>=0; i--)
    {
    	reversedPotatoes.push_back(potatoes[i]);
    }

    while (turkeysize>=0)
    {
    	int tcalorie = turkeys.back();
    	turkeys.pop_back();

    	int pcalorie = reversedPotatoes.back();
    	reversedPotatoes.pop_back();

    	pair<int,int> calories;
    	calories = make_pair(tcalorie, pcalorie);

    	plates.push_back(calories);

    	turkeysize--;
    }

	plates.pop_back();

    vector<pair<int,int> >::iterator it=plates.begin();

    int caloriesum = it->first + it->second;
    
    for (it=plates.begin()+1; it!=plates.end(); ++it)
    {
    	int temp =it->first + it->second;

    	if(caloriesum!=temp)
    	{
    		vector<pair<int,int> > empty;
    		return empty;
    	}

    	caloriesum = temp;
    }

  	return plates;
}