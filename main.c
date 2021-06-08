#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main(void)
{
  initscr();

  printw("Hallo Welt!");

  refresh();
  getch();
  endwin();
  return 0;
}
