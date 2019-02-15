
#pragma once

#include <iostream>
#include "snake_draw.h"
#include "snake.h"


class WindowHandler : public Gtk::Window
{
    public:
    
    WindowHandler();
    virtual ~WindowHandler();

    protected:

    bool on_key_press_event(GdkEventKey* key_event);

    void Init_timeout();

    sigc::connection m_connections;

    private:

    snake::dir new_dir;

    bool b_new_dir;

    snake current_snake;

    snake_draw draw_field;

    bool main_loop(int);

    int m_timeout;

    void reset_timeout_conn();

    sigc::connection conn;



};