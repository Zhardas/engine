#ifndef HEADACHE_TYPES_H
#define HEADACHE_TYPES_H

struct Position {
    int x;
    int y;

    Position(int x, int y) {
        this->x = x;
        this->y = y;
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
