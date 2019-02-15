#include "WindowHandler.h"

extern int speed;

int visual_speed = 5;


WindowHandler::WindowHandler()
{

    draw_field.set_snake(&current_snake);

    add(draw_field);

    set_size_request(500,500);

    add_events(Gdk::KEY_PRESS_MASK);

    Init_timeout();

    new_dir = snake::dir::up;
}

WindowHandler::~WindowHandler()
{

}

bool WindowHandler::main_loop(int some_integer)
{
    if(b_new_dir)
    {
      current_snake.change_dir(new_dir);

      b_new_dir = false;
    }

    current_snake.main_loop();

    draw_field.force_redraw();

    if(current_snake.game_over())
    {
      return false;
    }

    return true;
}

void WindowHandler::Init_timeout()
{

  sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &WindowHandler::main_loop), m_timeout);

  conn = Glib::signal_timeout().connect(my_slot, speed);

}

void WindowHandler::reset_timeout_conn()
{
    
    conn.disconnect();

    Init_timeout();
}

bool WindowHandler::on_key_press_event(GdkEventKey* key_event)
{
  if(key_event->keyval == GDK_KEY_w)
  {
    new_dir = snake::dir::up;

    b_new_dir = true;

    return true;
  }
  else if(key_event->keyval == GDK_KEY_s)
  {
    new_dir = snake::dir::down;

    b_new_dir = true;    

    return true;
  }
  else if(key_event->keyval == GDK_KEY_a)
  {
    new_dir = snake::dir::left;

    b_new_dir = true;  

    return true;
  }
  else if(key_event->keyval == GDK_KEY_d)
  {

    new_dir = snake::dir::right;

    b_new_dir = true;

    return true;
  }
  else if(key_event->keyval == GDK_KEY_r)
  {
    if(current_snake.game_over())
    {
      Init_timeout();
    }

    current_snake.clear_snake();  
  }
  else if(key_event->keyval == GDK_KEY_plus)
  {
    if (visual_speed < 10)
    {

    visual_speed++;
    speed -= 10;

    reset_timeout_conn();
    }

  }
  else if(key_event->keyval == GDK_KEY_minus)
  {
    if (visual_speed > 1)
    {
    visual_speed--;

    speed += 10;

    reset_timeout_conn();
    }
  }
  else if(key_event->keyval == GDK_KEY_Escape)
  {

    hide();
    return true;
  }

  return Gtk::Window::on_key_press_event(key_event);
}
