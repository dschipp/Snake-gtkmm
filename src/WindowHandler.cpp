#include "WindowHandler.h"

extern int speed;
extern int score;
extern int first_tiles;

WindowHandler::WindowHandler()
{   
    random_dir();

    set_size_request(600,600);

    add_events(Gdk::KEY_PRESS_MASK);

    add(field);

    m_timer_number = 0;

    Init_timeout();
}

WindowHandler::~WindowHandler()
{

}

void WindowHandler::Init_timeout()
{

  sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &WindowHandler::MainLoop), m_timer_number);

  sigc::connection conn = Glib::signal_timeout().connect(my_slot, speed);

  m_connections[m_timer_number] = conn;

}

void WindowHandler::change_possible()
{
    if (last_dir == Snake::move::up && dir == Snake::move::down)
    {
      dir = last_dir;
    }
    if (last_dir == Snake::move::down && dir == Snake::move::up)
    {
      dir = last_dir;
    }
    if (last_dir == Snake::move::left && dir == Snake::move::right)
    {
      dir = last_dir;
    }
    if (last_dir == Snake::move::right && dir == Snake::move::left)
    {
      dir = last_dir;
    }
}

bool WindowHandler::MainLoop(int m_timer_number)
{
    change_possible();
    field.mainloop(dir);
    field.force_redraw();

    if(field.game_over())
    {
      return false;
    }

    return true;
}

void WindowHandler::restart()
{

    if(field.game_over())
    {
      Init_timeout();
    }

    field.clear_list();
    field.Init();

    random_dir();

    score = 0;
    first_tiles = 3;
}

void WindowHandler::speed_up()
{
  if(speed > 10)
  {
    speed = speed - 10;
  }

  m_connections[m_timer_number].disconnect();

  m_connections.erase(m_timer_number);

  Init_timeout();
  
}

void WindowHandler::speed_down()
{
  speed = speed + 10;

  m_connections[m_timer_number].disconnect();

  m_connections.erase(m_timer_number);

  Init_timeout();
}

void WindowHandler::random_dir()
{
  int rand_dir = 5;

  srand(time(NULL) + rand_dir);

  rand_dir = rand() % 4;

  switch (rand_dir)
  {
    case 0:
      dir = Snake::move::up;
      break;
    case 1:
      dir = Snake::move::down;
      break;
    case 2:
      dir = Snake::move::left;
      break;
    case 3:
      dir = Snake::move::right;
      break;
    default:
      break;
  }
}

bool WindowHandler::on_key_press_event(GdkEventKey* key_event)
{
  if(key_event->keyval == GDK_KEY_w)
  {
    last_dir = dir;
    dir = Snake::move::up;
    field.force_redraw();
    return true;
  }
  else if(key_event->keyval == GDK_KEY_s)
  {
    last_dir = dir;
    dir = Snake::move::down;
    field.force_redraw();
    return true;
  }
  else if(key_event->keyval == GDK_KEY_a)
  {
    last_dir = dir;
    dir = Snake::move::left;
    field.force_redraw();
    return true;
  }
  else if(key_event->keyval == GDK_KEY_d)
  {
    last_dir = dir;
    dir = Snake::move::right;
    field.force_redraw();
    return true;
  }
  else if(key_event->keyval == GDK_KEY_r)
  {
    restart();    
  }
  else if(key_event->keyval == GDK_KEY_plus)
  {
    speed_up();  
  }
  else if(key_event->keyval == GDK_KEY_minus)
  {
    speed_down();    
  }
  else if(key_event->keyval == GDK_KEY_Escape)
  {

    hide();
    return true;
  }

  return Gtk::Window::on_key_press_event(key_event);
}
