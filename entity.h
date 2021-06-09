#include <stdio.h>

typedef struct Vector{
    int x, y;
} Vector;

Vector inlineVector(int,int);
void setVector(Vector*, int x, int y);
void setVectorX(Vector*, int x);
void setVectorY(Vector*, int y);

char* vectorToString(char*, Vector*);

typedef struct Snake {
    Vector* points;
    int length;
    int maxLength;
} Snake;

Snake initSnake(int,int);
void SnakeMoveTo(Snake*, Vector*);
void SnakeMoveInDir(Snake*, Vector*);
void SnakeUpdate(Snake*);
int SnakeSizeMax(Snake*);