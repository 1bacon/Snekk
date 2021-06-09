#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "entity.h"

#define FPS 15
#define UNICODE
#define DEBUG

#if defined UNICODE
#define MIDDLE_HORIZONTAL '═'
#define MIDDLE_VERTICAL '║'
#define TOP_LEFT '╔'
#define TOP_RIGHT '╗'
#define BOTTOM_LEFT '╚'
#define BOTTOM_RIGHT '╝'
#else
#define MIDDLE_HORIZONTAL '-'
#define MIDDLE_VERTICAL '|'
#define TOP_LEFT '+'
#define TOP_RIGHT '+'
#define BOTTOM_LEFT '+'
#define BOTTOM_RIGHT '+'
#endif


clock_t t, t_t;

int stop = 0;

int mx = 0;
int my = 0;

double deltaTime = 16;
double deltaTime_t = 16;
int frameCount = 0;

Snake s;
Vector apple;

void debug_draw()
{
  const char lines[10][50];
  sprintf(lines[0], "frameCount: %d", frameCount);
  sprintf(lines[1], "deltaT: %f", deltaTime);
  sprintf(lines[2], "deltaT_t: %f", deltaTime_t);
  sprintf(lines[3], "x: %d, y: %d", s.points[0].x, s.points[0].y);
  sprintf(lines[4], "size: %d", s.length);
  sprintf(lines[5], "mx: %d, my: %d", mx, my);
  int n = 6;
  int lo = 0;
  for (int i = 0; i < n; i++)
  {
    int l = strlen(lines[i]);
    lo = l > lo ? l : lo;
    mvprintw(i + 1, mx - l - 1, lines[i]);
  }
  for (int i = 1; i < n+1; i++)
  {
    mvprintw(i, mx - lo - 2, "|");
  }
  char a[50];
  sprintf(a,"%s%.*s", "+",lo,"------------------------------------"); 
  mvprintw(n+1, mx - lo - 2, a);
}

void setApple()
{
  start:;
  int rx = rand() * (double)((double)mx / (double)RAND_MAX);
  int ry = rand() * (double)((double)my / (double)RAND_MAX);

  for (int i = 0; i < s.length; i++)
  {
    if ((s.points[i].x == rx && s.points[i].y == ry) || rx < 1 || ry < 1 ||rx >= mx-1 || ry >= my-1  )
      goto start;
  }

  apple.x = rx;
  apple.y = ry;
  mvprintw(ry+1,rx+1,"o");
}

void gameLoop()
{

  s = initSnake(5,100);
  cbreak();
  nodelay(stdscr, 1);

  s.points[0].x = mx / 2;
  s.points[0].y = my / 2;
  Vector movement;
  setVector(&movement, 1, 0);

  setApple();

  while (!stop)
  {
    t_t = clock();
    double d = 1000.0 / FPS - deltaTime < 0 ? 0 : 1000.0 / FPS - deltaTime;
    usleep(1000 * d);
    t = clock();
    char input = getch();
    flushinp();

    switch (input)
    {
    case 'w':
      movement.y != 1 ? setVector(&movement, 0, -1) : movement.y;
      break;
    case 's':
      movement.y != -1 ? setVector(&movement, 0, 1) : movement.y;
      break;
    case 'a':
      movement.x != 1 ? setVector(&movement, -1, 0) : movement.x;
      break;
    case 'd':
      movement.x != -1 ? setVector(&movement, 1, 0) : movement.x;
      break;
    case 'e':
      s.length++;
      break;
    case 27:
      stop = 1;
      break;
    }



    SnakeUpdate(&s);
    SnakeMoveInDir(&s, &movement);

    mvprintw(s.points[SnakeSizeMax(&s)].y+1, s.points[SnakeSizeMax(&s)].x+1, " ");
    mvprintw(s.points[0].y+1, s.points[0].x+1, "#");

    if (s.points[0].x == apple.x && s.points[0].y == apple.y)
    {
      s.length++;
      setApple();
    }
    for (int i = 1; i < s.length; i++)
    {
      if(s.points[0].x == s.points[i].x && s.points[0].y == s.points[i].y){
        stop = 1;
      }
    }

    clock_t elapsed = 1000 * (clock() - t);
    deltaTime = ((double)elapsed) / CLOCKS_PER_SEC;
    deltaTime_t = ((double)1000 * (clock() - t_t)) / CLOCKS_PER_SEC;
    frameCount++;
    #if defined DEBUG
      debug_draw();
    #endif

    move(0, 0);
  };
}

int main()
{

  srand(time(NULL));
  initscr();            
  raw();                
  keypad(stdscr, TRUE); 
  noecho();             

  mx = getmaxx(stdscr);
  my = getmaxy(stdscr);

  box(stdscr, '|', '-');

  gameLoop();

  endwin();
  return 0;
}
