#include "SnakeObj.h"

extern int width;
extern int height;

SnakeObj::SnakeObj(int xC, int yC): x(xC), y(yC)
{
    lastX = 0;
    lastY = 0;  

    border_right = width/10;
    border_top = height/10;
}

SnakeObj::~SnakeObj()
{

}

void SnakeObj::genxyCoord()
{
    srand(time(NULL));

    do{
        x = rand() % (width-border_right) + border_right;
        y = rand() % (height-border_top) + border_top;
    }while (x== 0 || y == 0);

}

int SnakeObj::getX()
{
    return x;
}

int SnakeObj::getY()
{
    return y;
}

void SnakeObj::left()
{
    lastX = x;
    lastY = y;
    if(x == border_right)
    {
        x = height-1;
    }
    else
    {
        x = x-1;
    }
}

void SnakeObj::right()
{
   lastX = x;
    lastY = y;
   if(x == height-1)
   {
       x = border_right;
   }
   else
   {
       x = x +1;
   }
}

void SnakeObj::down()
{
    lastX = x;
   lastY = y;
    if(y == width-1)
    {
        y = border_top;
    }
    else
    {   
        y = y +1;
    }
}

void SnakeObj::up()
{
    lastX = x;
   lastY = y;
    if(y == border_top)
    {
        y = width-1;
    }
    else
    {   
        y = y - 1;
    } 
}

void SnakeObj::setX(int Nx)
{
    lastX = x;
   lastY = y;
    x = Nx;
}

void  SnakeObj::setY(int Ny)
{
    lastX = x;
   lastY = y;
    y = Ny;
}

int SnakeObj::getLastX()
{
    return lastX;
}

int SnakeObj::getLastY()
{
    return lastY;
}

void SnakeObj::setXY(int new_X, int new_Y)
{
    lastX = x;
    lastY = y;

    x = new_X;
    y = new_Y;
}

