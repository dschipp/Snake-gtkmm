#include <iostream>
#include "WindowHandler.h"

int width = 25;
int height = 25;
int score = 0;
int first_tiles = 3;
int speed = 100;

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    WindowHandler window;

    window.show_all();

    return app->run(window);
}