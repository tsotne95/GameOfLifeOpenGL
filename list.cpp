#include "list.h"
#include <iostream>
using namespace std;

void list::insert(cell *c)
{
    if(list::first == NULL)
    {
        list::first = c;
        list::last = c;
    }
    else
    {
        list::last->setnext(c);
        list::last = c;
    }
}
list::~list()
{
    p = false;
    current = first;
    cell *tmp = getcurrent();
    while(tmp!=NULL)
    {
        cell *aux = tmp;
        tmp = tmp->getnext();
        delete aux;
    }
}

list::list()
{
    list::first = NULL;
    list::last = NULL;
    list::current = NULL;
    list::p = false;
}


cell *list::getcurrent()
{
    if(!p)
    {
        cell *ret = NULL;
        if(list::first == NULL)
        {
            return NULL;
        }

        if(list::current == NULL)
        {
            list::current = list::first;
        }
        
        ret = list::current;

        if(list::current == list::last)
            list::p = true; 
        list::current = list::current->getnext();

        return ret;
    }
    else
        return NULL;
}

