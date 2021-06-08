#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FPS 15
#define UNICODE 1

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

typedef struct _Point
{
  int x, y;
} Point;

clock_t t, t_t;

int stop = 0;

int mx = 0;
int my = 0;

double deltaTime = 16;
double deltaTime_t = 16;
int frameCount = 0;

Point pos[100];
Point apple;

int size;

void debug_draw()
{
  const char lines[10][50];
  sprintf(lines[0], "frameCount: %d", frameCount);
  sprintf(lines[1], "deltaT: %f", deltaTime);
  sprintf(lines[2], "deltaT_t: %f", deltaTime_t);
  sprintf(lines[3], "x: %d, y: %d", pos[0].x, pos[0].y);
  sprintf(lines[4], "size: %d", size);
  int n = 5;
  int lo = 0;
  for (int i = 0; i < n; i++)
  {
    int l = strlen(lines[i]);
    lo = l > lo ? l : lo;
    mvprintw(i + 1, mx - l - 1, lines[i]);
  }
  for (int i = 1; i < 6; i++)
  {
    mvprintw(i, mx - lo - 2, "|");
  }
  char a[50];
  sprintf(a,"%.*s\n", lo-1,"------------------------------------"); 
  mvprintw(n+1, mx - lo - 1, a);
  mvprintw(n+1,mx-1,"\u2528");
}

void setApple()
{
  start:;
  int rx = rand() * (double)((double)mx / (double)RAND_MAX);
  int ry = rand() * (double)((double)my / (double)RAND_MAX);

  for (int i = 0; i < size; i++)
  {
    if (pos[i].x == rx && pos[i].y == ry || rx < 1 || ry < 1 ||rx >= mx-1 || ry >= my-1  )
      goto start;
  }

  apple.x = rx;
  apple.y = ry;
  mvprintw(ry,rx,"o");
}

void gameLoop()
{

  int dir = 0;
  int grow = 0;
  size = 5;
  cbreak();
  nodelay(stdscr, 1);

  pos[0].x = mx / 2;
  pos[0].y = my / 2;

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
      dir = dir != 3 ? 1 : dir;
      break;
    case 's':
      dir = dir != 1 ? 3 : dir;
      break;
    case 'a':
      dir = dir != 0 ? 2 : dir;
      break;
    case 'd':
      dir = dir != 2 ? 0 : dir;
      break;
    case 'e':
      grow = 1;
      break;
    case 27:
      stop = 1;
      break;
    }

    for (int i = size; i > 0; i--)
    {
      pos[i] = pos[i - 1];
    }

    switch (dir)
    {
    case 0:
      pos[0].x++;
      break;
    case 1:
      pos[0].y--;
      break;
    case 2:
      pos[0].x--;
      break;
    case 3:
      pos[0].y++;
      break;
    }
    if (grow)
    {
      size++;
      grow = 0;
    }
    else
    {
      mvprintw(pos[size].y, pos[size].x, " ");
    }
    mvprintw(pos[0].y, pos[0].x, "#");

    if (pos[0].x == apple.x && pos[0].y == apple.y)
    {
      size++;
      setApple();
    }
    for (int i = 1; i < size; i++)
    {
      if(pos[0].x == pos[i].x && pos[0].y == pos[i].y){
        stop = 1;
      }
    }

    clock_t elapsed = 1000 * (clock() - t);
    deltaTime = ((double)elapsed) / CLOCKS_PER_SEC;
    deltaTime_t = ((double)1000 * (clock() - t_t)) / CLOCKS_PER_SEC;
    frameCount++;
    debug_draw();

    move(0, 0);
  };
}

int main()
{

  srand(time(NULL));

  WINDOW *window;

  initscr();            /* Start curses mode 		*/
  raw();                /* Line buffering disabled	*/
  keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
  noecho();             /* Don't echo() while we do getch */

  mx = getmaxx(stdscr);
  my = getmaxy(stdscr);

  box(stdscr, '|', '-');

  gameLoop();

  endwin();
  return 0;
}
