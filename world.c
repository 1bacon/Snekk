#include "world.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

struct _Config
{

    int unicode;
    int style;

    int width;
    int height;
    int wrap;

    int debug;

    char up, down, left, right, pause, exit;
};

Config *initConfig()
{
    Config *c = calloc(1, sizeof(*c));
    return c;
}

struct _Time
{
    int frameRate;
    double frameTime;

    struct timeval last_start;
    struct timeval start;
};

Time *initTime(int frameRate)
{
    Time *t = malloc(sizeof(t));
    t->frameRate = frameRate;
    t->frameTime = 1.0 / frameRate;
    gettimeofday(&t->start, NULL);
    gettimeofday(&t->last_start, NULL);

    return t;
}

double deltaTime(Time *t)
{
    return (double)(t->start.tv_usec - t->last_start.tv_usec) / 1000000 + (double)(t->start.tv_sec - t->last_start.tv_sec);
}

void frameStart(Time *t)
{
    t->last_start = t->start;
    gettimeofday(&t->start, NULL);
}

void setFrameRate(Time *t, int fps)
{
    t->frameRate = fps;
}

void waitForFrameTime(Time *t)
{
    struct timeval tt;
    double secs;
    do
    {
        gettimeofday(&tt, NULL);
        secs = (double)(tt.tv_usec - t->start.tv_usec) / 1000000 + (double)(tt.tv_sec - t->start.tv_sec);
    } while (secs < t->frameTime);
}
