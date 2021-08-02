#include <time.h>

typedef struct _Time Time;
typedef struct _Config Config;

Config* initConfig();

Time *initTime(int);

double deltaTime(Time *t);

void frameStart(Time *);

void setFrameRate(Time *, int);
void waitForFrameTime(Time *);