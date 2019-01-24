#pragma once


#include <iostream>
#include <stdlib.h>
#include <time.h>

class FruitObj
{
    public:
    FruitObj();
    ~FruitObj();

    void genxyCoord();

    int getX();
    int getY();

    private:

    int border_top;
    int border_right;

    int x;
    int y;
};