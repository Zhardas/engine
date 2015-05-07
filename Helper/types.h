#ifndef HEADACHE_TYPES_H
#define HEADACHE_TYPES_H
#include <math.h>

struct Position {
    float x;
    float y;

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

    Size(int width, int height) {
        this->width = width;
        this->height = height;
    }
};

struct SizeF {
    float width;
    float height;

    SizeF(float width, float height) {
        this->width = width;
        this->height = height;
    }
};

#endif //HEADACHE_TYPES_H
