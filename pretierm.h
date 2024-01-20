/*
                                █████     ███                                     
                               ░░███     ░░░                                      
  ████████  ████████   ██████  ███████   ████   ██████  ████████  █████████████   
 ░░███░░███░░███░░███ ███░░███░░░███░   ░░███  ███░░███░░███░░███░░███░░███░░███  
  ░███ ░███ ░███ ░░░ ░███████   ░███     ░███ ░███████  ░███ ░░░  ░███ ░███ ░███  
  ░███ ░███ ░███     ░███░░░    ░███ ███ ░███ ░███░░░   ░███      ░███ ░███ ░███  
  ░███████  █████    ░░██████   ░░█████  █████░░██████  █████     █████░███ █████ 
  ░███░░░  ░░░░░      ░░░░░░     ░░░░░  ░░░░░  ░░░░░░  ░░░░░     ░░░░░ ░░░ ░░░░░  
  ░███                                                                            
  █████                                                                           
 ░░░░░                                                                            

#provided by leon zabalegui
*/



#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#ifdef _WIN32
 #include<windows.h>
#endif

namespace pretierm
{
    


#ifdef _WIN32
void INIT_PRETIERM()
{
 SetConsoleOutputCP(CP_UTF8);
 SetConsoleCP(CP_UTF8);
 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 if (hConsole == INVALID_HANDLE_VALUE){return;}
 DWORD dwMode;
 if (!GetConsoleMode(hConsole, &dwMode)){return;}
 dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
 if (!SetConsoleMode(hConsole, dwMode)){return;}

}
#endif

void clear_screen()
{
 std::cout<<"\033[2J\033[H";

}
void set_text_color(unsigned int r,unsigned int g,unsigned int b)
{
 std::cout<<"\033[38;2;"<<r<<";"<<g<<";"<<b<<"m";
}

void set_back_color(unsigned int r,unsigned int g,unsigned int b)
{
 std::cout<<"\033[48;2;"<<r<<";"<<g<<";"<<b<<"m";
}

void set_cursor_pos(int x,int y)
{
std::cout<<"\033["<<y+1<<";"<<x+1<<"H";
}



void draw_box(int x0,int y0,int x1,int y1,int selected_style)
{
if (x0>x1)
{
x0=x0^x1;
x1=x0^x1;
x0=x0^x1;
}

if (y0>y1)
{
y0=y0^y1;
y1=y0^y1;
y0=y0^y1;
}

std::vector<std::vector<std::string>>styles=
{
{"╔","╗","╚","╝","║","═"},
{"┌","┐","└","┘","│","─"},
{"╭","╮","╰","╯","│","─"},
{"┏","┓","┗","┛","┃","━"},

//THE UGLY ONE
{"/","\\","\\","/","|","-"},
};

set_cursor_pos(x0,y0);
std::cout<<styles[selected_style][0];
for (size_t i = x0; i < x1-1; ++i)
{
 std::cout<<styles[selected_style][5];
}
std::cout<<styles[selected_style][1];
for (size_t i = y0+1; i < y1; ++i)
{
 set_cursor_pos(x0,i); 
 std::cout<<styles[selected_style][4];
 set_cursor_pos(x1,i); 
 std::cout<<styles[selected_style][4];
}
set_cursor_pos(x0,y1);
std::cout<<styles[selected_style][2];
for (size_t i = x0; i < x1-1; ++i)
{
 std::cout<<styles[selected_style][5];
}
std::cout<<styles[selected_style][3];
}

void draw_line(int x0,int y0,int x1,int y1,std::string fill)
{
    x1-=1;
    y1-=1;
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    while (true) {

        if (x0 == x1 && y0 == y1) {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err = err - dy;
            x0 = x0 + sx;
        }
        if (e2 < dx) {
            err = err + dx;
            y0 = y0 + sy;

        }
        set_cursor_pos(x0,y0);
        std::cout<<fill;
    }
}

void draw_progress_bar(int x,int y,int bar_size,float perscentage,int selected_style)
{
std::vector<std::vector<std::string>>
styles=
{
{"[","═"," ","]"},
{"░","▓"," ","░"},
{"╠","═"," ","╣"},
{"[","/"," ","]"},
};
set_cursor_pos(x,y);
float half=x+((bar_size*0.01)*perscentage);
std::cout<<styles[selected_style][0];
for (unsigned short i = x; i < bar_size; ++i)
{
 if (i<half)
 {std::cout<<styles[selected_style][1];}
 else
 {std::cout<<styles[selected_style][2];}
}
std::cout<<styles[selected_style][3]<<" "<<perscentage<<"%";
}


void draw_line_graff(int x,int y,int bar_size,std::vector<float>persentages,std::string fill)
{
 for (unsigned short i = 0; i < persentages.size(); i++)
 {
  for (unsigned short n = bar_size; n > (bar_size-(bar_size*0.01)*persentages[i]); --n)
  {
    set_cursor_pos(x+i,y+n);
    std::cout<<fill;
  }
  

 }
}

void draw_triangle(int x0,int y0,int x1,int y1,int x2,int y2,std::string fill)
{
draw_line(x0,y0,x1,y1,fill);
draw_line(x1,y1,x2,y2,fill);
draw_line(x2,y2,x0,y0,fill);
}

void draw_list(int x,int y,std::vector<std::string>list,int selected_style)
{
std::vector<std::vector<std::string>>
  styles=
   {
    {"╔","╚","╠"},
    {"┌","└","├"},
    {"╭","╰","├"},
    {"/-","\\-","|-"}
   };
  for (unsigned short i = 0; i < list.size(); i++)
    {
     set_cursor_pos(x,y+i);
     if (i==0)
      {std::cout<<styles[selected_style][0]<<list[i];}
     else if (i==list.size()-1)
      {std::cout<<styles[selected_style][1]<<list[i];}
     else 
      {std::cout<<styles[selected_style][2]<<list[i];}
    }
}



void draw_char_map(int x,int y,std::vector<std::string>map)
{
for (unsigned short i = 0; i < map.size(); i++)
{
set_cursor_pos(x,y+i);
std::cout<<map[i];
}
}

}

