#ifndef HEADACHE_TYPES_H
#define HEADACHE_TYPES_H
#include <math.h>

struct Position {
  float x;
  float y;

  Position() {
    this->x = 0.0f;
    this->y = 0.0f;
  }

  Position(float x, float y) {
    this->x = x;
    this->y = y;
  }
  float Distance(const Position &p) {
    auto a = fabsf(fmaxf(x, p.x) - fminf(x, p.x));
    auto b = fabsf(fmaxf(y, p.y) - fminf(y, p.y));
    return sqrtf(a * a + b * b);
  }
  Position &operator+=(const Position &arg) {
    this->x += arg.x;
    this->y += arg.y;
    return *this;
  }
  Position operator*(const float &multiplier) {
    return Position(x * multiplier, y * multiplier);
  }
  Position &operator*=(const float &multiplier) {
    this->x *= multiplier;
    this->y *= multiplier;
    return *this;
  }
};

struct Position3 {
  float x;
  float y;
  float z;

  Position3() {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
  }

  Position3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  float Distance(Position *p) {
    auto a = fabsf(fmaxf(x, p->x) - fminf(x, p->x));
    auto b = fabsf(fmaxf(y, p->y) - fminf(y, p->y));
    return sqrtf(a * a + b * b);
  }

  float Distance(Position3 *p) {
    auto a = fabsf(fmaxf(x, p->x) - fminf(x, p->x));
    auto b = fabsf(fmaxf(y, p->y) - fminf(y, p->y));
    auto c = fabsf(fmaxf(z, p->z) - fminf(z, p->z));
    return sqrtf(a * a + b * b + c * c);
  }
};

struct Size {
  float width;
  float height;

  Size() {
    this->width = 100.0f;
    this->height = 100.0f;
  }

  Size(float width, float height) {
    this->width = width;
    this->height = height;
  }

  Size operator*(const Size &multiplier) {
    return Size(width * multiplier.width, height * multiplier.height);
  }
};

#endif //HEADACHE_TYPES_H
