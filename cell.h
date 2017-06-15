#ifndef cellH
#define cellH
class cell
{
    public:
    cell(int , int );
    ~cell();
    int getcolumn();//Returns the column that this cell stores
    int getline();//Returns the line that this cell stores
    cell *getnext();//Returns the next cell
    void setnext(cell*);//Sets the next cell from this list

    private:

    int line;
    int column;
    cell *next;
};
#endif
