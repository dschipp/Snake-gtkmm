#pragma once

#include <iostream>
#include <list>
#include "Snake_Objects/objects.h"
#include "Snake_Objects/fruit.h"
#include "Snake_Objects/snake_part.h"

using namespace std;


class snake{

    public:

    snake();
    ~snake();

    enum dir{
        up,
        down,
        left,
        right
    };

    void move();

    void change_dir(dir);

    void add_snake();

    bool check_fruit();

    bool game_over();

    void Init();

    void main_loop();

    bool change_possible(dir);

    fruit current_fruit;

    list<snake_part*> list_snake;

    void clear_snake();

    void random_dir();


    private:

    dir current_dir;

    bool b_add_snake;

    void add_to_snake(int,int);

    void spawn_new_fruit();

    int m_first_tiles;


    
};