#ifndef HEADACHE_TYPES_H
#define HEADACHE_TYPES_H
#include <math.h>

struct Position {
    float x;
    float y;

    Position(){
        this->x = 0.0f;
        this->y = 0.0f;
    }

    Position(float x, float y) {
        this->x = x;
        this->y = y;
    }
    float Distance(Position* p){
        auto a = fabsf(fmaxf(x, p->x) - fminf(x,p->x));
        auto b = fabsf(fmaxf(y, p->y) - fminf(y,p->y));
        return sqrtf(a*a+b*b);
    }
};

struct Size {
    int width;
    int height;

    Size(){
        this->width = 100;
        this->height = 100;
    }

    Size(int width, int height) {
        this->width = width;
        this->height = height;
    }
};

struct SizeF {
    float width;
    float height;

    SizeF(){
        this->width = 100.0f;
        this->height = 100.0f;
    }

    SizeF(float width, float height) {
        this->width = width;
        this->height = height;
    }
};

#endif //HEADACHE_TYPES_H
