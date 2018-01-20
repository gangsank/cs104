#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior 
{
public:
    string weapon;
    int power;
};

//Feel free to modify the parameters if you need other values
bool skirmish(Warrior** protectors, Warrior** invaders, int skirmish_row,
		      int rows, int cols, int &reserves, ofstream &output)
{
    //returns true if the invaders breach the walls.

    if (skirmish_row>=rows && skirmish_row>=cols)
    {
        return false;
    }

    for (int i=0; i<rows; i++)
    {
        if (protectors[i][skirmish_row].weapon == "axe" && 
            invaders[skirmish_row][i].weapon == "sword")
        {
            output << "Invader killed" << endl;
            invaders[skirmish_row][i].power = 0;
            invaders[skirmish_row][i].weapon = "";
            continue;
        }

        else if (invaders[skirmish_row][i].weapon == "axe" && 
                protectors[i][skirmish_row].weapon =="sword")
        {
            bool found = false;
            for (int a=0; a<cols; a++)
            {
                for (int b=0; b<rows; b++)
                {
                    if (invaders[a][b].power==0)
                    {
                        invaders[a][b]=protectors[i][skirmish_row];
                        output << "Protector defected" << endl;
                        found = true;
                        break;
                    }
                }
            }

            if (!found)
            {
                protectors[i][skirmish_row].power = 0;
                protectors[i][skirmish_row].weapon = "";
                output << "Protector killed" << endl;

                if (reserves>0)
                {
                    protectors[i][skirmish_row].power = 100;
                    protectors[i][skirmish_row].weapon = "axe";
                    --reserves;
                }
                continue;
            }
        }

        else if (protectors[i][skirmish_row].weapon == "axe" && 
            invaders[skirmish_row][i].weapon == "axe")
        {
            if (protectors[i][skirmish_row].power ==
                invaders[skirmish_row][i].power)
            {
                output << "Duel ends in draw" << endl;
            }

            else if (protectors[i][skirmish_row].power >
                    invaders[skirmish_row][i].power)
            {
                output << "Invader killed" << endl;
                invaders[skirmish_row][i].power =0;
                invaders[skirmish_row][i].weapon="";
                continue;
            }

            else
            {
                bool found = false;
                for (int a=0; a<cols; a++)
                {
                    for (int b=0; b<rows; b++)
                    {
                        if (invaders[a][b].power==0)
                        {
                            invaders[a][b]=protectors[i][skirmish_row];
                            output << "Protector defected" << endl;
                            found = true;
                            break;
                        }
                    }
                }

                if (!found)
                {
                    protectors[i][skirmish_row].power = 0;
                    protectors[i][skirmish_row].weapon = "";
                    output << "Protector killed";
                
                    if (reserves>0)
                    {
                        protectors[i][skirmish_row].power = 100;
                        protectors[i][skirmish_row].weapon = "axe";
                        --reserves;
                    }
                }

                continue;
            }
        }

        else if (protectors[i][skirmish_row].weapon == "sword" && 
            invaders[skirmish_row][i].weapon == "sword")
        {
            if (protectors[i][skirmish_row].power ==
                invaders[skirmish_row][i].power)
            {
                output << "Duel ends in draw" << endl;
            }

            else if (protectors[i][skirmish_row].power >
                    invaders[skirmish_row][i].power)
            {
                output << "Invader killed" << endl;
                invaders[skirmish_row][i].power =0;
                invaders[skirmish_row][i].weapon="";
                continue;
            }

            else
            {
                bool found = false;
                for (int a=0; a<cols; a++)
                {
                    for (int b=0; b<rows; b++)
                    {
                        if (invaders[a][b].power==0)
                        {
                            invaders[a][b]=protectors[i][skirmish_row];
                            output << "Protector defected" << endl;
                            found = true;
                            break;
                        }
                    }
                }

                if (!found)
                {
                    protectors[i][skirmish_row].power = 0;
                    protectors[i][skirmish_row].weapon = "";
                    output << "Protector killed";
                
                    if (reserves>0)
                    {
                        protectors[i][skirmish_row].power = 100;
                        protectors[i][skirmish_row].weapon = "axe";
                        --reserves;
                    }
                }
                continue;
            }
        }
               
        if (protectors[i][skirmish_row].power==0 && 
            invaders[skirmish_row][i].power>0)
        {
            return true;
        }

        else if (protectors[i][skirmish_row].power > 0 &&
                invaders[skirmish_row][i].power == 0)
        {
            output << "No assault" << endl;
        }
    }     
    return false;
}


int main(int argc, char* argv[])
{
    if (argc < 3) {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    bool result=false;
    int rows;
    int cols;
    int reserve;
    int skirmishes;

    //read the input file and initialize the values here.

    input >> rows;
    input >> cols;
    input >> reserve;
    input >> skirmishes;

    Warrior **protectors;
    Warrior **invaders;
  
    //initialize the protectors and invaders here.
    protectors = new Warrior* [rows];
    for (int i=0; i<rows; i++)
    {
        protectors[i] = new Warrior [cols];
    }

    invaders = new Warrior* [cols];
    for (int i=0; i<cols; i++)
    {
        invaders[i] = new Warrior [rows];
    }

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            protectors[i][j].power = i*10+((j+1)*10);
            
            if (i%2==0)
            {
                protectors[i][j].weapon = "axe";
            }

            else
            {
                protectors[i][j].weapon = "sword";
            }
        }
    }

    for (int i=0; i<cols; i++)
    {
        for (int j=0; j<rows; j++)
        {
            invaders[i][j].power = i*10+(j+1)*10;

            if (i%2==1)
            {
                invaders[i][j].weapon = "axe";
            }

            else
            {
                invaders[i][j].weapon = "sword";
            }
        }
    }

    for (int i=1; i <= skirmishes; i++){
        int skirmish_row;
        
        //read the input file to find the value for skirmish row
        input >> skirmish_row;
        
        //In general, it is bad style to throw everything into your main function
        bool end = skirmish(protectors, invaders, skirmish_row, 
            rows, cols, reserve, output);
        
        if (end)
        {
            result = end;
            break;
        }
    }

    //output the winner and deallocate your memory.
    if (result)
    {
        output << "Winner: invaders" << endl;
    }

    else
    {
        output << "Winner: protectors" << endl;
    }

    for (int i=0; i<rows; i++)
    {
      delete [] protectors[i];
    }
    delete [] protectors;

    for (int k=0; k<cols; k++)
    {
      delete [] invaders[k];
    }
    delete [] invaders;

    return 0;
}
