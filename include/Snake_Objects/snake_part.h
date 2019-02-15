#pragma once

#include <iostream>

#include "Snake_Objects/objects.h"

class snake_part : public objects{
    
    public:

    snake_part();
    virtual ~snake_part();

    void gen_x_y(int ,int);

    void set_x_y(int, int);

};

