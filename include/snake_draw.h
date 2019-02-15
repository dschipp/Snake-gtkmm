#pragma once

#include <iostream>
#include <gtkmm.h>
#include "snake.h"
#include <string>

class snake_draw : public Gtk::DrawingArea
{

    public:
    
    snake_draw();

    virtual ~snake_draw();

    void set_and_read_HighScore();

    void force_redraw();

    void set_snake(snake*);

    protected:

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    int HighScore;

    snake* current_snake;

    void draw_text(const Cairo::RefPtr<Cairo::Context>& cr, int x_pos, int y_pos, std::string);

    void set_and_read_HighScore_dat();
};
