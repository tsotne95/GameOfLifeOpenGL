#include "cell.h"
#include <stdlib.h>
using namespace std;
cell::~cell()
{
    cell::next = NULL;
}
cell::cell(int line, int column)
{
    cell::line = line;
    cell::column = column;
    cell::next = NULL;
}
int cell::getcolumn()
{
    return cell::column;
}

int cell::getline()
{
    return cell::line;
}

cell *cell::getnext()
{
    return cell::next;
}

void cell::setnext(cell *c)
{
    cell::next = c;
}
