#include "snake_draw.h"
#include "Snake_Objects/objects.h"
#include "Snake_Objects/fruit.h"
#include "Snake_Objects/snake_part.h"
#include <fstream>

extern int height;
extern int width;
extern int score;
int HighScore = 0;
extern int visual_speed;

snake_draw::snake_draw()
{
    Gtk::Allocation allocation = get_allocation();

    int win_height = allocation.get_height();

    set_size_request(win_height, win_height);
}

snake_draw::~snake_draw()
{

}

void snake_draw::set_snake(snake* new_snake)
{
    current_snake = new_snake;
}

void snake_draw::force_redraw()
{
    auto win = get_window();
    if (win)
    {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r, false);
    }

    set_and_read_HighScore_dat();
}

bool snake_draw::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();
    int win_width = allocation.get_width();
    int win_height = allocation.get_height();

    int tiles_height = win_height / height;
    int tiles_width = win_width / width;

    draw_text(cr, 24, 0,"Score : " + to_string(score), tiles_height, tiles_width);
    draw_text(cr,330,0,"Hight Score : " + to_string(HighScore), tiles_height, tiles_width);
    draw_text(cr,200,0,"Speed : " + to_string(visual_speed), tiles_height, tiles_width);

    int x1,x2,y1,y2;

    cr->set_line_width(5.0);

    cr->move_to(tiles_width,tiles_height);
    cr->line_to(tiles_width*(width-1), tiles_height);
    cr->line_to(tiles_width*(width-1),tiles_height*(height-1));
    cr->line_to(tiles_width,tiles_height*(height-1));
    cr->line_to(tiles_width,tiles_height);

    cr->stroke();

    for(auto it = current_snake->list_snake.begin(); it != current_snake->list_snake.end(); it ++)
    {
        

        x1 = ((*it)->get_x()+0.05)*tiles_width;
        y1 = ((*it)->get_y()+0.05)*tiles_height;
        x2 = ((*it)->get_x()+1-0.05)*tiles_width;
        y2 = ((*it)->get_y()+1-0.05)*tiles_height; 

        cr->move_to(x1,y1);
        cr->line_to(x1,y2);
        cr->line_to(x2,y2);
        cr->line_to(x2, y1);
        cr->line_to(x1, y1);
        cr->fill();
        cr->stroke();
    }

    cr->set_line_width(1.0);

    cr->arc((current_snake->current_fruit.get_x()+0.5)*tiles_width, (current_snake->current_fruit.get_y()+0.5)*tiles_height, tiles_width/2 , 0.0, 2.0 * M_PI);
    cr->set_source_rgba(1.0, 0.0, 0.0, 1.0);
    cr->fill_preserve();

    cr->stroke();



    return true;
}

void snake_draw::draw_text(const Cairo::RefPtr<Cairo::Context>& cr, int x_pos, int y_pos, std::string to_print, int tiles_height, int tiles_width)
{
    Pango::FontDescription font;

    font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_BOLD);

    string sScore = to_print;


    auto layout = create_pango_layout(sScore);

    layout->set_font_description(font);

    int text_width = tiles_width;
    int text_height = tiles_height;

    layout->get_pixel_size(text_width, text_height);

    cr->move_to(x_pos, y_pos);

    layout->show_in_cairo_context(cr);
}

void snake_draw::set_and_read_HighScore_dat()
{
    if(score > HighScore)
    {
        ofstream outfile("HighScore.dat");

        outfile << score << endl;
    }

    ifstream infile("HighScore.dat");

    infile >> HighScore;
}
