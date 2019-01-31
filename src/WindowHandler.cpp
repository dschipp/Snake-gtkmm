#include "WindowHandler.h"

extern int speed;
extern int score;
extern int first_tiles;
extern int visual_speed;

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

bool WindowHandler::move_possible(Snake::move to_change_dir, Snake::move to_test_dir)
{
    if (to_change_dir == Snake::move::up && new_dir == Snake::move::down)
    {
      return false;
    }
    if (to_change_dir == Snake::move::down && new_dir == Snake::move::up)
    {
      return false;
    }
    if (to_change_dir == Snake::move::left && new_dir == Snake::move::right)
    {
      return false;
    }
    if (to_change_dir == Snake::move::right && new_dir == Snake::move::left)
    {
      return false;
    }

  return true;

}

bool WindowHandler::MainLoop(int m_timer_number)
{

    if(!queue_dir.empty() && move_possible(dir, queue_dir.front()))
    {
        last_dir = dir;
        dir = queue_dir.front();
        field.mainloop(dir);
        field.force_redraw();
    }
    else
    {
        field.mainloop(dir);
        field.force_redraw();
    }

    if(!queue_dir.empty())
    {
      queue_dir.pop();
    }

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
  if(visual_speed < 10)
  {
    speed = speed - 10;
    visual_speed = visual_speed + 1;
  

  m_connections[m_timer_number].disconnect();

  m_connections.erase(m_timer_number);

  Init_timeout();

  }
  
}

void WindowHandler::speed_down()
{
  if(visual_speed > 1)
  {
    speed = speed + 10;
    visual_speed = visual_speed - 1;
  

  m_connections[m_timer_number].disconnect();

  m_connections.erase(m_timer_number);

  Init_timeout();
  }
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
    new_dir = Snake::move::up;

    queue_dir.push(new_dir);

    return true;
  }
  else if(key_event->keyval == GDK_KEY_s)
  {
    new_dir = Snake::move::down;

    queue_dir.push(new_dir);

    return true;
  }
  else if(key_event->keyval == GDK_KEY_a)
  {
    new_dir = Snake::move::left;

    queue_dir.push(new_dir);

    return true;
  }
  else if(key_event->keyval == GDK_KEY_d)
  {
    new_dir = Snake::move::right;

    queue_dir.push(new_dir);

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
