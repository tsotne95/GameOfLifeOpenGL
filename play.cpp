
#include "play.h"
#include <iostream>
using namespace std;
play::~play()
{
    for (int i = 0; i < lineS; i ++)
    {
        generationcurrent = NULL;
        nextgeneration = NULL;
        delete generation1[i];
        delete generation2[i];
    }
    delete listcells;
}
bool play::getcell(int line,int column)
{
    return play::generationcurrent[line][column];
}



play::play()
{
    listcells = new list();
    int i,j;

    play::generation1 =new bool*[lineS];
    play::generation2 =new bool*[lineS];
    for(i = 0; i < lineS; i++)
    {
        play::generation1[i] = new bool[columnS];
        play::generation2[i] = new bool[columnS];
    }

    for( i =0; i < lineS; i++)
    {
        for(j = 0; j < columnS; j++)
        {
            play::generation1[i][j] = false;
            play::generation2[i][j] = false;
        }
    }
    play::generationcurrent = play::generation1;
    play::nextgeneration = play::generation2;
}

void play::resetgeneration(bool **generation)
{
    int i,j;
    for(i = 0; i < lineS; i++)
    {
        for (j = 0; i < columnS; j++)
        {
            generation[i][j] = false;
        }
    }
}

void play::printgeneration(bool **generation)
{
    int i,j;
    for( i =0; i < lineS; i++)
    {
        for(j = 0; j < columnS; j++)
        {
            cout << generation[i][j];
        }
    }
}

void play::calculatenextgeneration()
{
    int i,j;

    delete nextgeneration;
    nextgeneration = new bool*[lineS];
    for (i = 0; i < lineS; i++)
        nextgeneration[i] =  new bool[columnS];
    delete listcells;
    listcells = new list();

    for( i = 0; i < lineS; i++)
    {
        for(j = 0; j < columnS; j++)
        {
            if(generationcurrent[i][j])//se tiver vivo, trata ela
            {
                cell c(i,j);
                int numneighbors = countneighbors(&c,generationcurrent) ;
                if( (numneighbors == 2) || (numneighbors==3))
                {
                    nextgeneration[i][j] = true;
                }
                else
                {
                    nextgeneration[i][j] = false;
                }
            }
            else
            {
                nextgeneration[i][j] = false;
            }
        }
    }
    cell *tmp = listcells->getcurrent();
    while(tmp!=NULL)
    {
        int n = countneighbors(tmp, generationcurrent);
        if (n == 3)
        {
            nextgeneration[tmp->getline()][tmp->getcolumn()] = true;
        }
        tmp = tmp->getnext();
    }
}

void play::changegenerations()
{
    bool **tmp = generationcurrent;
    play::generationcurrent = nextgeneration;
    nextgeneration = tmp;

}

int play::countneighbors(cell *c, bool **generation)
{
    
    int numberneighbors = 0;
    int i = c->getline();
    int j = c->getcolumn();

    if(i > 0)
    {
        if(generationcurrent[i-1][j])
        {
            numberneighbors++;
        }
        else if(generationcurrent[i][j])
        {
            cell *c = new cell(i-1,j);
            listcells->insert(c);
        }

        if(j > 0)
        {
            if(generationcurrent[i-1][j-1])
            {
                numberneighbors++;
            }
            else if(generationcurrent[i][j])
            {
                cell *c= new cell(i-1,j-1);
                listcells->insert(c);
            }
        }

        if(j < columnS-1)
        {
            if(generationcurrent[i-1][j+1])
            {
                numberneighbors++;
            }
            else if(generationcurrent[i][j])
            {
                cell *c=new cell(i-1,j+1);
                listcells->insert(c);
            }
        }
    }

    if(i<lineS-1)
    {
        if(generationcurrent[i+1][j])
        {
            numberneighbors++;
        }
        else if(generationcurrent[i][j])
        {
            cell *c= new cell(i+1,j);
            listcells->insert(c);
        }


        if(j > 0)
        {
            if(generationcurrent[i+1][j-1])
            {
                numberneighbors++;
            }
            else if(generationcurrent[i][j])
            {
                cell *c=new cell(i+1,j-1);
                listcells->insert(c);
            }
        }

        if(j < columnS-1)
        {
            if(generationcurrent[i+1][j+1])
            {
                numberneighbors++;
            }
            else if(generationcurrent[i][j])
            {
                cell *c=new cell(i+1,j+1);
                listcells->insert(c);
            }
        }
    }
    if(j>0)
    {
        if(generationcurrent[i][j-1])
        {
            numberneighbors++;
        }
        else if(generationcurrent[i][j])
        {
            cell *c=new cell(i,j-1);
            listcells->insert(c);
        }
    }
    if(j<columnS-1)
    {
        if(generationcurrent[i][j+1])
        {
            numberneighbors++;
        }
        else if(generationcurrent[i][j])
        {
            cell *c=new cell(i,j+1);
            listcells->insert(c);
        }
    }
    return numberneighbors;
}

bool **play::getnextgeneration()
{
    return play::nextgeneration;
}

bool **play::getgenerationcurrent()
{
    return play::generationcurrent;
}

void play::setcell(cell *c, bool status)
{
    generationcurrent[c->getline()][c->getcolumn()] = status;
}
