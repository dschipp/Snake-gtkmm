#include "Snake_Objects/objects.h"
#include "Snake_Objects/fruit.h"
#include "Snake_Objects/snake_part.h"

objects::objects()
{

}

objects::~objects()
{

}

int objects::get_x()
{
    return x_coord;
}

int objects::get_y()
{
    return y_coord;
}

void objects::set_x(int new_x)
{
    x_coord = new_x;
}

void objects::set_y(int new_y)
{
    y_coord = new_y;
}

fruit::fruit()
{

}

fruit::~fruit()
{

}

void fruit::gen_x_y(int smallest, int highest)
{
    srand(time(NULL)+1);

    set_x(rand() % highest + smallest);
    set_y(rand() % highest + smallest);
}

snake_part::snake_part()
{

}

snake_part::~snake_part()
{

}

void snake_part::gen_x_y(int smallest, int highest)
{
    srand(time(NULL));

    set_x(rand() % highest + smallest);
    set_y(rand() % highest + smallest);
}

void snake_part::set_x_y(int new_x, int new_y)
{
    set_x(new_x);
    set_y(new_y);
}