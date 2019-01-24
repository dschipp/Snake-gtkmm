#include "Spielfeld.h"

using namespace std;

extern int width;
extern int height;

Spielfeld::Spielfeld()
{
    SnakeObj *s = new SnakeObj(0,0);

    s->genxyCoord();

    fruit.genxyCoord();
	
    snake.push_back(s);

}

Spielfeld::~Spielfeld()
{
    for(auto it = snake.begin(); it != snake.end(); it ++)
    {
        delete (*it);
    }
}

void Spielfeld::mainloop(Spielfeld::move dir)
{
        moveSnake(dir);
        if(checkonFruit())
        {
            addSnake();
            fruit.genxyCoord();
        }    
}


void Spielfeld::moveSnake(move Move0)
{
   std::list<SnakeObj*>::iterator its;

   switch(Move0)
   {
    case move::up :
        for(auto it = snake.begin(); it != snake.end(); it++)
        {
            if(it == snake.begin())
                {
                    (*it)->up();
                }
            else
                {
                    (*it)->setXY((*its)->getLastX(),  (*its)->getLastY());
                }
            its = it;
        }
        break;
    case move::down :
        for(auto it = snake.begin(); it != snake.end(); it++)
        {
            if(it == snake.begin())
                {
                    (*it)->down();
                }
            else
                {
                    (*it)->setXY((*its)->getLastX(),  (*its)->getLastY());
                }
            its = it;
        }
        break;
    case move::left :
        for(auto it = snake.begin(); it != snake.end(); it++)
        {
            if(it == snake.begin())
                {
                    (*it)->left();
                }
            else
                {
                    (*it)->setXY((*its)->getLastX(),  (*its)->getLastY());
                }
            its = it;
        }
        break;
    case move::right :
        for(auto it = snake.begin(); it != snake.end(); it++)
        {
            if(it == snake.begin())
                {
                    (*it)->right();
                }
            else
                {
                    (*it)->setXY((*its)->getLastX(),  (*its)->getLastY());
                }
            its = it;
        }
        break;
    default :
        std::cout << "Unmöglich aber man weiß ja nie" << endl;
   }
}

void Spielfeld::addSnake()
{
    SnakeObj *s = new SnakeObj(0,0);
	
    snake.push_back(s);
}

bool Spielfeld::checkonFruit()
{
    for(auto it = snake.begin(); it != snake.end(); it++)
    {
        if((*it)->getX()==fruit.getX() && (*it)->getY()==fruit.getY())
        {
            return true;
        }
    }
    return false;
}

bool Spielfeld::game_over()
{
    for(auto it = snake.begin(); it != snake.end(); it++)
    {
        for(auto jt = snake.begin(); jt != snake.end(); jt++)
        {
            if((*it)->getX() == (*jt)->getX() && (*it)->getY() == (*jt)->getY() && it != jt)
            {
                return true;
            }
        }
    }

    return false;
}

bool Spielfeld::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{

  cr->set_line_width(5.0);

  Gtk::Allocation allocation = get_allocation();
  int winWidth = allocation.get_width();
  int winHeight = allocation.get_height();

  double Xscale, Yscale, xRand, yRand;

  xRand = winWidth / 20;
  yRand = winHeight / 20;

  Xscale = (xRand*19 / width);
  Yscale = (yRand*19 / height);

  cr->move_to(xRand, yRand);
  cr->line_to(xRand, yRand*19);
  cr->line_to(xRand*19, yRand*19);
  cr->line_to(xRand*19, yRand);
  cr->line_to(xRand, yRand);
  cr->stroke();

  //

  cr->set_line_width(10.0);

  int x1, y1, x2, y2;

for(auto it = snake.begin(); it != snake.end(); it ++)
    {
        

        x1 = (*it)->getX()*Xscale;
        y1 = (*it)->getY()*Yscale;
        x2 = ((*it)->getX()+1)*Xscale;
        y2 = ((*it)->getY()+1)*Yscale; 

        cr->move_to(x1,y1);
        cr->line_to(x1,y2);
        cr->line_to(x2,y2);
        cr->line_to(x2, y1);
        cr->line_to(x1, y1);
        cr->fill();
        cr->stroke();
    }

  cr->set_line_width(1.0);

  cr->arc((fruit.getX()+0.5)*Xscale, (fruit.getY()+0.5)*Yscale, Xscale/2 , 0.0, 2.0 * M_PI);
  cr->set_source_rgba(1.0, 0.0, 0.0, 1.0);
  cr->fill_preserve();

  cr->stroke();

  return true;
}

void Spielfeld::force_redraw()
{
  auto win = get_window();
  if (win)
  {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r, false);
  }
}