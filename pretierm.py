#                                █████     ███                                     
#                               ░░███     ░░░                                      
#  ████████  ████████   ██████  ███████   ████   ██████  ████████  █████████████   
# ░░███░░███░░███░░███ ███░░███░░░███░   ░░███  ███░░███░░███░░███░░███░░███░░███  
#  ░███ ░███ ░███ ░░░ ░███████   ░███     ░███ ░███████  ░███ ░░░  ░███ ░███ ░███  
#  ░███ ░███ ░███     ░███░░░    ░███ ███ ░███ ░███░░░   ░███      ░███ ░███ ░███  
#  ░███████  █████    ░░██████   ░░█████  █████░░██████  █████     █████░███ █████ 
#  ░███░░░  ░░░░░      ░░░░░░     ░░░░░  ░░░░░  ░░░░░░  ░░░░░     ░░░░░ ░░░ ░░░░░  
#  ░███                                                                            
#  █████                                                                           
# ░░░░░                                                                            
#provided by leon zabalegui

import os,random,time


def INIT_PRETIERM():
 if os.name=="nt":
    import ctypes
    from ctypes import wintypes
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

def set_console_font(font_size_x, font_size_y,font_name):
 if os.name=="nt":
  import ctypes
  from ctypes import wintypes
  class CONSOLE_FONT_INFOEX(ctypes.Structure):
        _fields_ = [("cbSize", ctypes.c_ulong),
                    ("nFont", ctypes.c_ulong),
                    ("dwFontSize", wintypes._COORD),
                    ("FontFamily", ctypes.c_uint),
                    ("FontWeight", ctypes.c_uint),
                    ("FaceName", wintypes.WCHAR * 32)]
  font_info = CONSOLE_FONT_INFOEX()
  font_info.cbSize = ctypes.sizeof(CONSOLE_FONT_INFOEX)
  font_info.nFont = 0
  font_info.dwFontSize.X = font_size_x
  font_info.dwFontSize.Y = font_size_y
  font_info.FontFamily = 0
  font_info.FontWeight = 400
  ctypes.windll.kernel32.lstrcpyW(font_info.FaceName, font_name)
  handle = ctypes.windll.kernel32.GetStdHandle(-11)
  ctypes.windll.kernel32.SetCurrentConsoleFontEx(handle, False, ctypes.byref(font_info))

def clear_screen():
 print("\033[2J\033[H",end="")

def set_text_color(r=int,g=int,b=int):
 print(f"\033[38;2;{r};{g};{b}m",end="")

def set_back_color(r=int,g=int,b=int):
 print(f"\033[48;2;{r};{g};{b}m",end="")

def set_cursor_pos(x,y):
 print(f"\033[{y+1};{x+1}H",end="")

def reset_text():
 print("\033[0m",end="")

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

   #THE UGLY ONE
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


def draw_triangle(x0,y0,x1,y1,x2,y2,fill):
 draw_line(x0,y0,x1,y1,fill)
 draw_line(x1,y1,x2,y2,fill)
 draw_line(x2,y2,x0,y0,fill)

def draw_list(x,y,list_strings,selected_style):
 styles=[
  ["╔","╚","╠"],
  ["┌","└","├"],
  ["╭","╰","├"],
  
  #THE UGLY ONE
  ["/-","\\-","|-"]
 ]
 for i in range(len(list_strings)):
  set_cursor_pos(x,y+i)
  if i==0:
   print(styles[selected_style][0]+str(list_strings[i]),end="")
  elif i==len(list_strings)-1:
   print(styles[selected_style][1]+str(list_strings[i]),end="")
  else:
   print(styles[selected_style][2]+str(list_strings[i]),end="")


def draw_char_map(x,y,map):
 for i in range(len(map)):
  set_cursor_pos(x,y+i)
  print(map[i],end="")

def draw_color_map(x,y,map):
 for i in range(0,int(len(map))-1,2):
  for n in range(len(map[i])):
   set_cursor_pos(x+n,(y+int(i/2)))
   set_back_color(map[i][n][0],map[i][n][1],map[i][n][2])
   set_text_color(map[i+1][n][0],map[i+1][n][1],map[i+1][n][2])
   print("▄",end="")



