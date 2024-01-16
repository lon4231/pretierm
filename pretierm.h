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

void INIT_PRETIERM()
{
#ifdef _WIN32
 SetConsoleOutputCP(CP_UTF8);
 SetConsoleCP(CP_UTF8);
 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 if (hConsole == INVALID_HANDLE_VALUE){return;}
 DWORD dwMode;
 if (!GetConsoleMode(hConsole, &dwMode)){return;}
 dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
 if (!SetConsoleMode(hConsole, dwMode)){return;}
#endif
}

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



void draw_box(int x0,int y0,int x1,int y1,int sel_style)
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
{"/","\\","\\","/","|","-"},
};

set_cursor_pos(x0,y0);
std::cout<<styles[sel_style][0];
for (size_t i = x0; i < x1-1; ++i)
{
 std::cout<<styles[sel_style][5];
}
std::cout<<styles[sel_style][1];
for (size_t i = y0+1; i < y1; ++i)
{
 set_cursor_pos(x0,i); 
 std::cout<<styles[sel_style][4];
 set_cursor_pos(x1,i); 
 std::cout<<styles[sel_style][4];
}
set_cursor_pos(x0,y1);
std::cout<<styles[sel_style][2];
for (size_t i = x0; i < x1-1; ++i)
{
 std::cout<<styles[sel_style][5];
}
std::cout<<styles[sel_style][3];
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
        set_cursor_pos(x0,y0);
        std::cout<<fill;
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
    }
}

void draw_progress_bar(int x,int y,int size,float pers,int sel_style)
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
float half=((size*0.01)*pers);
std::cout<<styles[sel_style][0];
for (size_t i = x; i < size; ++i)
{
 if (i<half)
 {std::cout<<styles[sel_style][1];}
 else
 {std::cout<<styles[sel_style][2];}
}
std::cout<<styles[sel_style][3]<<" "<<pers<<"%";
}


void draw_line_graff(int x,int y,int size_bars,std::vector<float>persentages,std::string fill)
{
 for (size_t i = 0; i < persentages.size(); i++)
 {
  for (size_t n = size_bars; n > (size_bars-(size_bars*0.01)*persentages[i]); --n)
  {
    set_cursor_pos(x+i,y+n);
    std::cout<<fill;
  }
  

 }
}