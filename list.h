#include "cell.h"
#ifndef listH
#define listH

class list
{
    public:
    list();
    ~list();
    cell* getcurrent();
    void insert(cell *);

    private:
    bool p;
    cell *first;
    cell *last;
    cell *current;
};

#endif
