import ctypes,os
from ctypes import wintypes


def INIT_PRETIERM():
 if os.name=="nt":
    kernel32 = ctypes.WinDLL('kernel32', use_last_error=True)
    kernel32.SetConsoleOutputCP(ctypes.c_uint(65001))  # CP_UTF8
    kernel32.SetConsoleCP(ctypes.c_uint(65001))        # CP_UTF8
    STD_OUTPUT_HANDLE = -11
    hConsole = kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
    if hConsole == wintypes.HANDLE(-1):
        
        return
    dwMode = ctypes.c_uint()
    if not kernel32.GetConsoleMode(hConsole, ctypes.byref(dwMode)):
        return
    dwMode.value |= 0x0004
    kernel32.SetConsoleMode(hConsole, dwMode)


def clear_screen():
 print("\033[2J\033[H",end="")

def set_text_color(r=int,g=int,b=int):
 print(f"\033[38;2;{r};{g};{b}m",end="")

def set_back_color(r=int,g=int,b=int):
 print(f"\033[38;2;{r};{g};{b}m",end="")

def set_cursor_pos(x,y):
 print(f"\033[{y+1};{x+1}H",end="")

def draw_box(x0,y0,x1,y1,selected_style):
 if x0>x1:
  x0,x1=x1,x0
 if y0>y1:
  y0,y1=y1,y0
 styles=[
   ["╔","╗","╚","╝","║","═"],
   ["┌","┐","└","┘","│","─"],
   ["╭","╮","╰","╯","│","─"],
   ["┏","┓","┗","┛","┃","━"],
   ["/","\\","\\","/","|","-"]
 ]
 set_cursor_pos(x0,y0)
 print(styles[selected_style][0],end="")
 for i in range(x0,x1-1):
   print(styles[selected_style][5],end="")
 print(styles[selected_style][1],end="")
 for i in range(y0+1,y1):
  set_cursor_pos(x0,i)
  print(styles[selected_style][4],end="")
  set_cursor_pos(x1,i)
  print(styles[selected_style][4],end="")
 set_cursor_pos(x0,y1); 
 print(styles[selected_style][2],end="")
 for i in range(x0,x1-1):
   print(styles[selected_style][5],end="")
 print(styles[selected_style][3],end="")

def draw_line(x0,y0,x1,y1,fill):
 x1-=1;
 y1-=1;
 dx = abs(x1 - x0)
 dy = abs(y1 - y0)
 sx = 1 if x0 < x1 else -1
 sy = 1 if y0 < y1 else -1
 err = dx - dy
 while True:
  if x0 == x1 and y0 == y1:
   break
  e2 = 2 * err
  if e2 > -dy:
   err = err - dy
   x0+=sx
  if e2<dx:
   err=err+dx
   y0+=sy
  set_cursor_pos(x0,y0)
  print(fill,end="")

def draw_progress_bar(x,y,bar_size,perscentage,selected_style):
 styles=[
  ["[","═"," ","]"],
  ["░","▓"," ","░"],
  ["╠","═"," ","╣"],
  ["[","/"," ","]"]]
 set_cursor_pos(x,y)
 half=x+((bar_size*0.01)*perscentage)
 print(styles[selected_style][0],end="")
 for i in range(x,x+bar_size):
  if i<half:
   print(styles[selected_style][1],end="")
  else:
   print(styles[selected_style][2],end="")
 print(styles[selected_style][3]+str(perscentage)+"%",end="")

def draw_line_graff(x,y,bar_size,persentages,fill):
 for i in range(0,len(persentages)):
  for n in range(bar_size,int(bar_size-(bar_size*0.01)*persentages[i]),-1):
   set_cursor_pos(x+i,y+n)
   print(fill,end="")