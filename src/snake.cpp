#include "snake.h"
#include <time.h>
#include <unistd.h>

extern int width;
extern int height;
extern int score;
extern int first_tiles;

snake::snake()
{
    Init();
}

snake::~snake()
{

}

void snake::Init()
{
    snake_part* s = new snake_part;

    s->gen_x_y(1, height-1);

    list_snake.push_back(s);

    spawn_new_fruit();

    m_first_tiles = first_tiles;

    random_dir();
}

void snake::random_dir()
{
  int rand_dir = 5;

  srand(time(NULL) + rand_dir);

  rand_dir = rand() % 4;

  switch (rand_dir)
  {
    case 0:
      current_dir = dir::up;
      break;
    case 1:
      current_dir = dir::down;
      break;
    case 2:
      current_dir = dir::left;
      break;
    case 3:
      current_dir = dir::right;
      break;
    default:
      break;
  }
}

void snake::main_loop()
{
    move();
    if(check_fruit())
    {
        spawn_new_fruit();
        add_snake();
    }
}

void snake::add_to_snake(int x_pos, int y_pos)
{
    if(b_add_snake || m_first_tiles > 1)
    {
        snake_part* s = new snake_part;

        s->set_x_y(x_pos, y_pos);

        b_add_snake = false;

        list_snake.push_back(s);

        if(m_first_tiles > 1)
        {
            m_first_tiles--;
        }
    }
}

void snake::spawn_new_fruit()
{
    bool spawn_again = false;

    do
    {
        current_fruit.gen_x_y(1,height-2);

        for(auto it = list_snake.begin(); it != list_snake.end(); it++)
        {
            if((*it)->get_x() == current_fruit.get_x() && (*it)->get_y() == current_fruit.get_y())
            {
                spawn_again = true;
                break;
            }
            else
            {
                spawn_again = false;
            }
        }
    }while(spawn_again);
}

void snake::move()
{
    auto snake_begin = list_snake.front();
    auto snake_end = list_snake.back();

    int safe_x, safe_y;

    safe_x = snake_end->get_x();
    safe_y = snake_end->get_y();

    switch (current_dir)
    {
        case dir::up:
            snake_end->set_x_y(snake_begin->get_x(), snake_begin->get_y()-1);
            break;
        case dir::down:
            snake_end->set_x_y(snake_begin->get_x(), snake_begin->get_y()+1);
            break;
        case dir::left:
            snake_end->set_x_y(snake_begin->get_x()-1, snake_begin->get_y());
            break;
        case dir::right:
            snake_end->set_x_y(snake_begin->get_x()+1, snake_begin->get_y());
            break;
    
        default:
            break;
    }

    if(snake_end->get_x() == 0)
    {
        snake_end->set_x(height-2);
    }
    else if (snake_end->get_x() == height-1)
    {
        snake_end->set_x(1);
    }
    else if(snake_end->get_y() == width-1)
    {
        snake_end->set_y(1);
    }
    else if(snake_end->get_y() == 0)
    {
        snake_end->set_y(width-2);
    }
    
    list_snake.push_front(snake_end);
    list_snake.pop_back();

    add_to_snake(safe_x, safe_y);
}

void snake::change_dir(dir new_dir)
{
    if(change_possible(new_dir))
    {
        current_dir = new_dir;
    }
}

void snake::add_snake()
{
    score++;
    b_add_snake = true;
}

bool snake::check_fruit()
{
    for(auto it = list_snake.begin(); it != list_snake.end(); it++)
    {
        if((*it)->get_x()==current_fruit.get_x() && (*it)->get_y()==current_fruit.get_y())
        {
            return true;
        }
    }
    return false;
}

bool snake::game_over()
{
    auto jt = list_snake.begin();

    for(auto it = list_snake.begin(); it != list_snake.end(); it++)
    {
        if((*it)->get_x() == (*jt)->get_x() && (*it)->get_y() == (*jt)->get_y() && it != jt)
        {
            return true;
        }
    }

    return false;
}

bool snake::change_possible(dir new_dir)
{
    if (current_dir == snake::dir::up && new_dir == snake::dir::down)
    {
      return false;
    }
    if (current_dir == snake::dir::down && new_dir == snake::dir::up)
    {
      return false;
    }
    if (current_dir == snake::dir::left && new_dir == snake::dir::right)
    {
      return false;
    }
    if (current_dir == snake::dir::right && new_dir == snake::dir::left)
    {
      return false;
    }

  return true;
}

void snake::clear_snake()
{
    list_snake.clear();

    score = 0;

    Init();
}