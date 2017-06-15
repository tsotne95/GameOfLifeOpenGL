#include "coordinates.h"
#include <math.h>
#include <iostream>
using namespace std;
coordinates::~coordinates()
{

}
coordinates::coordinates(double fX, double fY, double startX, double startY)
{
    coordinates::endX = fX;
    coordinates::endY = fY;
    coordinates::startX = startX;
    coordinates::startY = startY;
}
double coordinates::multiplicationY(double param)
{
    double t = (double)(endY*2) * param;
    return t;
}
double coordinates::multiplicationX(double param)
{
    double t = (double)(endX*2) * param;
    return t;
}
double coordinates::convertNormalParaworldX(double coordX)
{
    return round(multiplicationX(coordX) - endX);
}
double coordinates::convertDisplayParaNormalX(int x)
{
    double t = (double) x / widthWindow;
    return  t ;
}
double coordinates::display2worldX(int x)
{
    double normal = convertDisplayParaNormalX(x);
    double world = convertNormalParaworldX(normal);
    return world;
}


double coordinates::convertNormalParaworldY(double coordY)
{
    return round(multiplicationY(coordY) - endY);
}
double coordinates::convertDisplayParaNormalY(int y)
{
        double t = (double) y / heightWindow;
        return  t ;
}

double coordinates::display2worldY(int y)
{
    double normal = convertDisplayParaNormalY(y);
    int world = convertNormalParaworldY(normal);
    return world;
}

void coordinates::setSizeWindow(int w, int h)
{
    coordinates::heightWindow = h;
    coordinates::widthWindow = w;
}

int coordinates::worldParaMatrixLine(double worldLine)
{
    double l = (double) ((worldLine-startY) / (endY - startY));
    return round(l * columns);
}
int coordinates::worldParaMatrixcolumn(double worldcolumn)
{
    double c = (double) ((worldcolumn-startY) / (endY - startY));
    return round(c * lines);
}
void coordinates::setlines(int l)
{
    coordinates::lines = l;
}
void coordinates::setcolumns(int c)
{
    coordinates::columns = c;
}
