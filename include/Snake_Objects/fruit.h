#pragma once

#include <iostream>

#include "Snake_Objects/objects.h"

class fruit : public objects{
    
    public:

    fruit();
    virtual ~fruit();

    void gen_x_y(int, int);

};
