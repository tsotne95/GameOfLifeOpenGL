#ifndef playH
#define playH
#define lineS 50
#define columnS 50
#include "cell.h"
#include "list.h"
class play
{
    public:
        play();
        ~play();
        void printgeneration(bool **);
        void calculatenextgeneration();
        bool **getgenerationcurrent();
        bool **getnextgeneration();
        void setcell(cell *, bool );
        int countneighbors(cell *,bool **);
        void resetgeneration(bool **);
        bool getcell(int,int);
        void changegenerations();
    private:
        bool **generation1;
        bool **generation2;

        bool **generationcurrent;
        bool **nextgeneration;
       
        list *listcells;

};
#endif
