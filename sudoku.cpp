#include "bits/stdc++.h"
using namespace std;


//First we will stire all the starting postions of the 9 squares
int units[9][2]={{0,0},{3,0},{6,0},{0,3},{0,6},{3,3},{3,6},{6,3},{6,6}};
unordered_map<int,int> unitsPositions,unitsPositions2; // starting position and its unit number


unordered_set<int> squaresInunits[9];
void fillUnits()
{
    int i,j,k,m,x,y,num;
    for(i=0;i<9;i++)
    {
        x=units[i][0];
        y=units[i][1];
        int unum=x*9+y;
        int unitStartingPoint=unitsPositions[num];
        for(k=y;k<y+3;k++)
        {
            num=x*9+k;
            squaresInunits[i].insert(num);
            unitsPositions[num]=unum;
        }
        for(k=x;k<x+3;k++)
        {
            num=k*9+y;
            squaresInunits[i].insert(num);
            unitsPositions[num]=unum;
        }
        x=x+1;
        y=y+1;
        for(k=y;k<y+2;k++)
        {
            num=x*9+k;
            squaresInunits[i].insert(num);
            unitsPositions[num]=unum;
        }
        for(k=x;k<x+2;k++)
        {
            num=k*9+y;
            squaresInunits[i].insert(num);
            unitsPositions[num]=unum;
        }
        x=x+1;
        y=y+1;
        num=x*9+y;
        squaresInunits[i].insert(x*9+y);
        unitsPositions[num]=unum;
    }
}



class Square
{
    public:
        int squareVal;
        unordered_set<int> peers;
        unordered_set<int> possibleDigits;
        
        //Square(int val) :  squareVal(val){}
        void setPossibleValuesForSquare(int x)
        {
            
        }
       
        void createPeerSet(int x,int y)
        {
            //1)Insert all elements in the same row
            int i,j,num;
            for(i=0;i<9;i++)
            {
                num=x*9+i;
                this->peers.insert(num);
            } 
            //cout<<"hi\n";
            //2)Insert all elements in the same column
            for(i=0;i<9;i++)
            {
                num=i*9+y;
                this->peers.insert(num);
            } 
            //3)Insert all elements in the same units.For this figure out the starting position of the units
            num=x*9+y;
            int startingUnitNum=unitsPositions[num];
            //cout<<"startingUnitNum is "<<startingUnitNum<<"\n";
            int unitNum=unitsPositions2[startingUnitNum];
            //cout<<"unitNum is "<<unitNum<<"\n";
            unordered_set<int>::iterator it;
            for(it=squaresInunits[unitNum].begin();it!=squaresInunits[unitNum].end();it++)
            {
                this->peers.insert(*it);
            }
            //Now we have the peer set for everything
            
            this->peers.erase(num);
        }
        
        void printPeerSet()
        {
            unordered_set<int>::iterator it;
            int size=this->peers.size();
            cout<<"the size of the peer set is "<<size<<"\n";
            for(it=this->peers.begin();it!=this->peers.end();it++)
            {
                cout<<*it<<" ";
            }
            cout<<"\n";
        }
};


Square Board[81],a;

unordered_map<int,unordered_set<int> >grid; //Since its easier to copy the unordered map we'll use that 
void createBoardDictionary()
{
    int i,j;

    for(i=0;i<81;i++)
    {
        if(Board[i].squareVal==0)
        {
            for(j=1;j<=9;j++)
            {
                grid[i].insert(j);
            }    
        }   
        else
        {
            grid[i].insert(Board[i].squareVal); //remmber to do constraint satisfaction initially
        }
    }
}



bool constraintStatisfaction2(unordered_map<int,unordered_set<int> >&grid,int assigned) //Pass the grid(unordered<map>) by reference since we need to make changes to it
{
    int i,j,squareVal;
    unordered_set<int>::iterator it,it2;
    i=assigned;
        //The set of Peers are Board[i].peers
        //Note , Only remove constraints if that paticular node is assigned a value
        if(grid[i].size()==1)
        {
            it2=grid[i].begin();
            squareVal=*it2;
            for(it=Board[i].peers.begin();it!=Board[i].peers.end();it++)
            {
                //cout<<"grid["<<*it<<"].size() is "<<grid[(*it)].size()<<"\n";
                //Check for the Values of the peers step by step.*it is the peer number, not its value. check its value in the map first
                if(grid[(*it)].size()==1 and *(grid[(*it)].begin())==squareVal)
                {
                    return false; //We have a violation of the constraint
                }
                if(grid[(*it)].size()!=1)
                {
                    //i.e. That particular peer has not been assigned a value yet, so we check 
                    //1) If that peer has the same value or not
                    if(grid[(*it)].find(squareVal)!=grid[(*it)].end()) //i.e. the peer has a contradiction value
                    {
                        //cout<<"we need to erase "<<squareVal<<" from "<<(*it)<<"\n";
                        grid[(*it)].erase(squareVal);
                    }
                    
                }
            }
            
        }
     
     return true;
    
}

void putSpaces(int num)
{
    int i;
    for(i=0;i<num;i++)
    {
        if(i==num/2)
        printf("|");
        else
        printf("_");
    }
}

void printBoard2(unordered_map<int,unordered_set<int> > grid)
{
    int i,j,m,numElementsInSet;
    unordered_set<int>::iterator it;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            m=i*9+j;
            numElementsInSet=grid[m].size();
            
            for(it=grid[m].begin();it!=grid[m].end();it++)
            {
                cout<<(*it);
            }
            putSpaces(5-numElementsInSet);
        }
        cout<<"\n";
    }
}
void printMap(unordered_map<int,unordered_set<int> >grid)
{
    int i,j;
    unordered_set<int>::iterator it;
    for(i=0;i<81;i++)
    {
        cout<<"For element number "<<i<<" its possible values are \n";
        for(it=grid[i].begin();it!=grid[i].end();it++)
        {
            printf(" %d ",*it);
        }
        cout<<"\n";
    }
}

bool finishedBoard(unordered_map<int,unordered_set<int> >grid)
{
    int i,j;
    for(i=0;i<81;i++)
    {
        if(grid[i].size()!=1)
        {
            return false;
        }
    }
    return true;
}

int mostConstrainedVariable(unordered_map<int,unordered_set<int> >grid,unordered_set<int> remaining)
{
    int i,j,mini=INT_MAX,size,mcv;
    if(finishedBoard(grid))
    {
        cout<<"Game Completed \n\n";
        printBoard2(grid);
        exit(0);
    }
    unordered_set<int>::iterator it;
    for(it=remaining.begin();it!=remaining.end();it++)
    {
        
        size=grid[(*it)].size();
        if(size < mini)
        {
            mini=size;
            mcv=*it;
        }
    }
    return mcv;
}



//int leastConstrainingValue
void search(unordered_map<int,unordered_set<int> >grid,int assignSquare,unordered_set<int> remaining)
{
    //So Now we have a varaible to begin with and a mcv square to which we need to assign a values
    //For starters lets just assign turn by turn without using the lcv
    if(finishedBoard(grid))
    {
        cout<<"Game Completed \n\n";
        printBoard2(grid);
        exit(0);
    }
    unordered_set<int>::iterator it,it2;
    bool status;
   
    int mcv;
    //cout<<"assigning square "<<assignSquare<<"\n";
    remaining.erase(assignSquare);
    for(it=grid[assignSquare].begin();it!=grid[assignSquare].end();it++)// since the grid contains all the possible numbers that can fit into the square
    {
        //So basically we want to try all the possible values and then propogate the constraints
        unordered_map<int,unordered_set<int> > nextGrid=grid;
        nextGrid[assignSquare].clear(); //clear all the possible values
        nextGrid[assignSquare].insert(*it);//Insert the first possible value 
        //Now we nned to check for constaint Propogation, which eliminates all the possible values among its peers.
        //If the constraintStatisfaction returns false then we need to try a different assignment, else we continue our search
        status=constraintStatisfaction2(nextGrid,assignSquare);
        //cout<<"status is "<<status<<"\n";
        if(status)
        {
            //then we continue with our backtracking search
            //cout<<"now prining board\n";
            //printBoard2(nextGrid);
            //cout<<"\n\n";
            //First we find the next square to assign value to or color the square from 1-9 colors. This is so cool man!!!!!!!!!
            mcv=mostConstrainedVariable(nextGrid,remaining);
            //cout<<"next mcv is "<<mcv<<"\n";
            search(nextGrid,mcv,remaining);
        }
        else
        {
            continue;
        }
        
    }
}

int main()
{
    int i,j,k;
    
    unitsPositions2[0]=0;
    unitsPositions2[27]=1;
    unitsPositions2[54]=2;
    unitsPositions2[3]=3;
    unitsPositions2[6]=4;
    unitsPositions2[30]=5;
    unitsPositions2[33]=6;
    unitsPositions2[57]=7;
    unitsPositions2[60]=8;
    fillUnits();
    //pboard();
    unordered_set<int>::iterator it;
    /*cout<<"\n the peers in the each unit are\n";
    for(i=0;i<9;i++)
    {
        cout<<"In square "<<i<<" the peers are \n";
        for(it=squaresInunits[i].begin();it!=squaresInunits[i].end();it++)
        {
            cout<<*it<<" ";
        }     
        cout<<"\n";       
    }*/
    //Now we input the board
    //cout<<"juo\n";
    int x;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            //cout<<"hi2\n";
            
           scanf("%d",&x);

           Board[i*9+j].squareVal=x;
           //cout<<"Board["<<i*9+j<<"].squareVal is "<<Board[i*9+j].squareVal<<"\n";
           Board[i*9+j].createPeerSet(i,j);
          // cout<<"done\n";
        }
    }
    //cout<<" enter a square nummber to get its peerset \n";
    int sx=0,sy;
    /*while(sx<81)
    {
        

        cout<<"sx is "<<sx<<"\n";
        Board[sx++].printPeerSet();
        
    }*/
    createBoardDictionary();
    //constraintStatisfaction(grid);
    //cout<<"\n\n Now we'll print our first Board\n\n";
    //printMap(grid);
    //printBoard2(grid);
    unordered_set<int> remaining;
    for(i=0;i<81;i++)
    {
        remaining.insert(i);   
    }
    //Now we have the board configration with its peers
    //Now lets call the search function
    int mcv=mostConstrainedVariable(grid,remaining);
    search(grid,mcv,remaining);
    return 0;
}
