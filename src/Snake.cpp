#include "Snake.h"
#include <string>
#include <fstream>

using namespace std;

extern int width;
extern int height;
extern int score;
extern int speed;
extern int first_tiles;

Snake::Snake()
{
    Init();
}

Snake::~Snake()
{
    for(auto it = snake.begin(); it != snake.end(); it ++)
    {
        delete (*it);
    }
}

void Snake::mainloop(Snake::move dir)
{
        moveSnake(dir);
        if(!(first_tiles <= 1))
        {
            add_to_Snake();
            first_tiles -= 1;
            score = 0;
        }
        if(ckeck_eat_fruit())
        {
            add_to_Snake();
            while(checkonFruit())
            {
                fruit.genxyCoord();
            }
        }    
}

bool Snake::ckeck_eat_fruit()
{
    auto it = snake.begin();

    if((*it)->getX() == fruit.getX()
            && (*it)->getY() == fruit.getY())
    {
                return true;
    }

    return false;
}


void Snake::moveSnake(move Move0)
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

void Snake::add_to_Snake()
{

    auto last_Snake = snake.rend();
    last_Snake++;

    SnakeObj *s = new SnakeObj((*last_Snake)->getLastX(),(*last_Snake)->getLastY());
	
    snake.push_back(s);

    score++;
}

bool Snake::checkonFruit()
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

bool Snake::game_over()
{
    auto jt = snake.begin();

    for(auto it = snake.begin(); it != snake.end(); it++)
    {
        if((*it)->getX() == (*jt)->getX() && (*it)->getY() == (*jt)->getY() && it != jt)
        {
            return true;
        }
    }

    return false;
}

bool Snake::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{

  Gtk::Allocation allocation = get_allocation();
  int winWidth = allocation.get_width();
  int winHeight = allocation.get_height();

  double Xscale, Yscale, x_border_bottom, y_border_bottom, x_border_top, y_border_top;

  x_border_bottom = winWidth - 50;
  y_border_bottom = winHeight -50;
  x_border_top = 50;
  y_border_top = 50;

  draw_score(cr, x_border_top, y_border_top-20);
  draw_HighScore(cr, x_border_bottom - 128, y_border_top-20);
  draw_speed(cr, x_border_bottom / 2 , y_border_top - 20);

  cr->set_line_width(5.0);


  cr->move_to(x_border_top, y_border_top);
  cr->line_to(x_border_top, y_border_bottom);
  cr->line_to(x_border_bottom, y_border_bottom);
  cr->line_to(x_border_bottom, y_border_top);
  cr->line_to(x_border_top, y_border_top);
  cr->stroke();


  Xscale = ((x_border_bottom) / width);
  Yscale = ((y_border_bottom) / height);

  //

  cr->set_line_width(10.0);

  int x1, y1, x2, y2;

for(auto it = snake.begin(); it != snake.end(); it ++)
    {
        

        x1 = ((*it)->getX()+0.05)*Xscale;
        y1 = ((*it)->getY()+0.05)*Yscale;
        x2 = ((*it)->getX()+1-0.05)*Xscale;
        y2 = ((*it)->getY()+1-0.05)*Yscale; 

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

void Snake::force_redraw()
{
  auto win = get_window();
  if (win)
  {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r, false);
  }
}

void Snake::clear_list()
{
    snake.clear();
}

void Snake::Init()
{
    SnakeObj *s1 = new SnakeObj(0,0);

    s1->genxyCoord();

    fruit.genxyCoord();
	
    snake.push_back(s1);
}

void Snake::draw_score(const Cairo::RefPtr<Cairo::Context>& cr, int x_pos, int y_pos)
{  
  Pango::FontDescription font;

  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_BOLD);

  string sScore = "Score : " + to_string(score);


  auto layout = create_pango_layout(sScore);

  layout->set_font_description(font);

  int text_width;
  int text_height;

  layout->get_pixel_size(text_width, text_height);

  cr->move_to(x_pos, y_pos);

  layout->show_in_cairo_context(cr);

}

void Snake::draw_HighScore(const Cairo::RefPtr<Cairo::Context>& cr, int x_pos, int y_pos)
{

  set_and_read_HighScore();

  Pango::FontDescription font;

  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_BOLD);

  string sScore = "High Score : " + to_string(HighScore);


  auto layout = create_pango_layout(sScore);

  layout->set_font_description(font);

  int text_width;
  int text_height;

  layout->get_pixel_size(text_width, text_height);

  cr->move_to(x_pos, y_pos);

  layout->show_in_cairo_context(cr);

}

void Snake::draw_speed(const Cairo::RefPtr<Cairo::Context>& cr, int x_pos, int y_pos)
{
    set_and_read_HighScore();

  Pango::FontDescription font;

  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_BOLD);

  string sSpeed = "Speed : " + to_string(speed);


  auto layout = create_pango_layout(sSpeed);

  layout->set_font_description(font);

  int text_width;
  int text_height;

  layout->get_pixel_size(text_width, text_height);

  cr->move_to(x_pos, y_pos);

  layout->show_in_cairo_context(cr);
}

void Snake::set_and_read_HighScore()
{
    if(score > HighScore)
    {
        ofstream outfile("HighScore.dat");

        outfile << score << endl;
    }

    ifstream infile("HighScore.dat");

    infile >> HighScore;
}