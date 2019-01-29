#pragma once

#include "gtkmm.h"
#include "Snake.h"
#include <map>
#include <queue>

class WindowHandler : public Gtk::Window
{
    public:
    WindowHandler();
    virtual ~WindowHandler();

    bool MainLoop(int);

    void Init_timeout();

    void random_dir();

    private:

    int m_timer_number;
    int timeout_value;

    Snake field;

    protected:

    void restart();

    bool on_key_press_event(GdkEventKey* event) override;

    Snake::move dir;

    Snake::move last_dir;

    Snake::move new_dir;

    void change_possible();

    void speed_up();

    void speed_down();

    std::map<int, sigc::connection> m_connections;

    std::queue<Snake::move> queue_dir;

};