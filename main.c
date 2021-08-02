#include "entity.h"
#include "world.h"
#include "states.h" 

#include <curses.h>


int main()
{
    Time *t = initTime(5);
    Config *c = initConfig();

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    while (1)
    {
        waitForFrameTime(t);
        frameStart(t);

        executeCurrentFullFrame();
    }
}