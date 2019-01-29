#include <iostream>
#include "WindowHandler.h"
#include <time.h>

int width = 30;
int height = 30;
int speed = 90;
int score = 0;
int first_tiles = 3;
int visual_speed = 5;

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    WindowHandler window;

    window.show_all();

    return app->run(window);
}
