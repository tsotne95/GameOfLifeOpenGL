
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "list.h"
#include "cell.h"
#include "play.h"
#include "coordinates.h"
using namespace std;
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#define start_X -50
#define end_X 50
#define start_Y -50
#define end_Y 50

int win_width = 500;
int win_height = 500;
float pointsize = 1;
play j;
coordinates *c;
coordinates *matrixParaworld;
bool autogeneration = false;



void menugeneration(int);
void showMenu(void);
void timer(int);
void configuration(void);
void treatMouse(int, int, int, int);
void drawGrade(void);
void drawgeneration(bool **);
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);

void menugeneration(int option)
{
    if(option == 1)
    {
        j.calculatenextgeneration();
        j.changegenerations();
        glutPostRedisplay();
    }
    if(option == 2)
    {
        if(autogeneration)
            autogeneration = false;
        else
        {
            glutTimerFunc(1000, timer, 1);
            autogeneration = true;
        }
    }

}

void showMenu()
{
    int menu = glutCreateMenu(menugeneration);
    glutAddMenuEntry("next generation (N)",1);
    glutAddMenuEntry("Calculate automatically (a)",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void timer(int t)
{
    if(t == 1)
    {
        if(autogeneration)
        {
            glutTimerFunc(1000, timer, 1);
            j.calculatenextgeneration();
            j.changegenerations();
            glutPostRedisplay();
        }
    }
}
void configuration()
{
    matrixParaworld = new coordinates(end_X, end_Y, start_X, start_Y);
    matrixParaworld->setSizeWindow(columnS, lineS);
    matrixParaworld->setlines(lineS);
    matrixParaworld->setcolumns(columnS);

    c = new coordinates(end_X, end_Y, start_X, start_Y);
    pointsize =  win_width / columnS;
    c->setSizeWindow(win_width, win_height);
}

void treatMouse(int button, int state, int x, int y)
{
    if( (button == GLUT_LEFT_BUTTON) &&(state == GLUT_DOWN) )
    {
        
        float line, column;

        
        line = -c->display2worldY(y);
        column = c->display2worldX(x);

        
        line = matrixParaworld->worldParaMatrixLine(-line);
        column = matrixParaworld->worldParaMatrixcolumn(column);

        
        if( (line < lineS ) && (line >= 0) && (column >= 0) && (column < columnS))
        {
            cell *tmp = new cell(line, column);
            j.setcell(tmp,!j.getcell(line,column));
            glutPostRedisplay();
        }
    }
    if( (button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN) )
    {
        showMenu();

    }

}

void drawgeneration(bool **generation)
{
    int i,j;
    for(i = 0; i < lineS; i++)
    {
        for(j = 0; j < columnS; j++)
        {
            if(generation[i][j])
            {
                glPointSize(pointsize);
                glBegin(GL_POINTS);
                    
                    glVertex2i(matrixParaworld->display2worldX(j),
                               -matrixParaworld->display2worldY(i));
                glEnd();
            }
        }
    }
}

void display( void )
{
    glMatrixMode(GL_MODELVIEW);
    glClear( GL_COLOR_BUFFER_BIT );

    glPushMatrix();
        glColor3ub(0,0,0);
        drawGrade();
        glColor3ub(255,127,0);
        drawgeneration(j.getgenerationcurrent());
    glPopMatrix();
    glFlush();
}
void reshape( int w, int h )
{
    
    glMatrixMode( GL_PROJECTION );
    glutPositionWindow(10,10);
    glutReshapeWindow(win_width,win_height);
    glLoadIdentity();
    glOrtho(start_X,end_X,start_Y,end_Y,-1,1);
    glViewport( 0, 0, win_width, win_height );
    glutPostRedisplay();
}
void keyboard( unsigned char key, int x, int y )
{
  switch(key)
  {
    case 27: // Escape key
    {
        delete c;
        delete matrixParaworld;
        exit(0);
        break;
    }
    case 'n':
    {
        menugeneration(1);
        break;
    }
    case 'N':
    {
        menugeneration(1);
        break;
    }
  //  case 'a':
  //    {
  //      autogeneration = true;
        //break;
  //    }

  }
}

int main (int argc, char *argv[])
{
    configuration();
    glutInit( &argc, argv );
    glMatrixMode(GL_PROJECTION);
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE );
    glutInitWindowSize( win_width, win_height );
    glutInitWindowPosition(10,10);

    glutCreateWindow( "Game of Life" );

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutMouseFunc(treatMouse);
    glClearColor(1,1,1,1);

    glutMainLoop();
}
void drawGrade(void)
{
    int i;
   
    float tmp = start_Y - pointsize/2;

    for(i= 0; i <= lineS+2; i++)
    {

        glBegin(GL_LINES);
            glVertex2f(start_X, tmp);
            glVertex2f(end_X, tmp);
        glEnd();
        tmp+=2;

    }
    tmp = start_X - pointsize/2;
    for(i = 0; i < columnS+3; i++)
    {
        glBegin(GL_LINES);
            glVertex2f(tmp, start_Y);
            glVertex2f(tmp, end_Y);
        glEnd();
        tmp+=2;
    }
}
