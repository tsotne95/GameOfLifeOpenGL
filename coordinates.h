#ifndef coordinates_H
#define coordinates_H
class coordinates
{
  public:
    coordinates(double endX, double endY, double startX, double startY );
    ~coordinates();
    double display2worldX(int );
    
    double display2worldY(int );

    void setSizeWindow(int, int);

    int worldParaMatrixLine(double worldLine);
    int worldParaMatrixcolumn(double worldcolumn);
    void setlines(int);
    void setcolumns(int);

  private:
    int heightWindow;
    int widthWindow;
    double endX;
    double endY;
    double startY;
    double startX;
    int lines;
    int columns;

    double multiplicationX(double );
    double multiplicationY(double );
    double convertNormalParaworldX(double );
    double convertNormalParaworldY(double );

    double convertDisplayParaNormalX(int );
    double convertDisplayParaNormalY(int );

    double normalParaDisplayY(double y);
    double normalParaDisplayX(double x);

    double convertworldParaNormalY(double y);
    double convertworldParaNormalX(double x);
};
#endif
