#include "entity.h"

Vector in;

Vector inlineVector(int x, int y){
    in.x = x;
    in.y = y;
    return in;
}

void setVector(Vector* v, int x, int y){
    v->x = x;
    v->y = y;
}

void setVectorX(Vector* v, int x){
    setVector(v,x,v->y);
}

void setVectorY(Vector* v, int y){
    setVector(v,v->x,y);
}

char* vectorToString(char* b, Vector* v){
    sprintf(b,"(%d,%d)",v->x,v->y);
    return b;
}

Snake initSnake(int initalLength, int maxLength){
    Snake s;
    s.points = malloc(initalLength * sizeof(Vector));
    s.length = initalLength;
    s.maxLength = maxLength;
    return s;
}
void SnakeMoveTo(Snake* s, Vector* v){
    s->points[0].x = v->x;
    s->points[0].y = v->y;
}
void SnakeMoveInDir(Snake* s, Vector* v){
    s->points[0].x = s->points[0].x + v->x;
    s->points[0].y = s->points[0].y + v->y;
}
void SnakeUpdate(Snake* s){
    for (int i = SnakeSizeMax(s); i > 0; i--)
    {
        s->points[i] = s->points[i - 1];
    }
}
int SnakeSizeMax(Snake* s){
    return s->length > s->maxLength ? s->maxLength : s->length; 
}
