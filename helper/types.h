#ifndef HELPER_TYPES_H_
#define HELPER_TYPES_H_
#include <math.h>
#include <iostream>
#include <string>
#include <functional>
#include <memory>

template<typename T>
using removable_unique_ptr = std::unique_ptr<T, std::function<void(T*)>>;


// Main vertex structure
struct v_3ct {
  float x, y, z;
  uint32_t color;
  float tu, tv;
};

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
  Position &operator-=(const Position &arg) {
    this->x -= arg.x;
    this->y -= arg.y;
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
  std::string ToString() {
    return "x: " + std::to_string(x) + " y: " + std::to_string(y);
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
inline std::ostream &operator<<(std::ostream &stream, Position const &position) {
  stream << "x: " << std::to_string(position.x) << " y: " << std::to_string(position.y);
  return stream;
}

inline std::ostream &operator<<(std::ostream &stream, Size const &size) {
  stream << "w: " << std::to_string(size.width) << " h: " << std::to_string(size.height);
  return stream;
}
#endif  // HELPER_TYPES_H_
