#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>

class SnakeObj
{
    public:
    SnakeObj(int, int);
    ~SnakeObj();

    void genxyCoord();

    int getX();
    int getY();

    void up();
    void down();
    void left();
    void right();

    void setX(int);
    void setY(int);

    void setXY(int, int);

    int getLastX();
    int getLastY();


    private:

    int border_top;
    int border_right;

    int x;
    int y;

    int lastX;
    int lastY;
};
