#pragma once

#include <gtkmm.h>
#include <iostream>
#include "SnakeObj.h"
#include "FruitObj.h"
#include <list>
#include <unistd.h>
#include <string>
#include <stdio.h>

class Spielfeld : public Gtk::DrawingArea
{

public:
    Spielfeld();
    ~Spielfeld();

enum move
    {
        up,
        down,
        left,
        right
    };

    void setfruit();

    void moveSnake(Spielfeld::move);

    void mainloop(Spielfeld::move);

    bool checkonFruit();

    void force_redraw();

    bool game_over();

private:


    void addSnake();

    std::list<SnakeObj*> snake;

    FruitObj fruit;

    protected:
    
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    
};