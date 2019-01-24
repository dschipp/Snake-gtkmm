#include "FruitObj.h"

extern int width;
extern int height;

FruitObj::FruitObj()
{
    genxyCoord();

    border_right = width/10;
    border_top = height/10;
}

FruitObj::~FruitObj()
{

}

void FruitObj::genxyCoord()
{
    srand(time(NULL)+1);

    do{
        x = rand() % (width-border_right) + border_right;
        y = rand() % (height-border_top) + border_top;
    }while (x== 0 || y == 0);

}

int FruitObj::getX()
{
    return x;
}

int FruitObj::getY()
{
    return y;
}