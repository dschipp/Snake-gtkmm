#pragma once

#include <iostream>

class objects{
    public:

    objects();
    virtual ~objects();

    int get_x();
    int get_y();

    void set_x(int);
    void set_y(int);

    virtual void gen_x_y(int, int) = 0;

    private:

    int x_coord;
    int y_coord;



};
