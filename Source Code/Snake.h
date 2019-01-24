#pragma once

#include <gtkmm.h>
#include <iostream>
#include "SnakeObj.h"
#include "FruitObj.h"
#include <list>
#include <unistd.h>
#include <string>
#include <stdio.h>

class Snake : public Gtk::DrawingArea
{

public:
    Snake();
    ~Snake();

enum move
    {
        up,
        down,
        left,
        right
    };

    void setfruit();

    void moveSnake(Snake::move);

    void mainloop(Snake::move);

    bool checkonFruit();

    void force_redraw();

    bool game_over();

    void Init();

    void clear_list();

    void draw_score(const Cairo::RefPtr<Cairo::Context>& cr, int x_pos, int y_pos);

    void draw_HighScore(const Cairo::RefPtr<Cairo::Context>& cr, int x_pos, int y_pos);

    void set_and_read_HighScore();

    void draw_speed(const Cairo::RefPtr<Cairo::Context>& cr, int x_pos, int y_pos);

private:


    void add_to_Snake();

    std::list<SnakeObj*> snake;

    FruitObj fruit;

    protected:
    
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    int HighScore;
    
};