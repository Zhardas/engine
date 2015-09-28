class Collidable;
#ifndef OVERLORD_COLLIDABLE_H
#define OVERLORD_COLLIDABLE_H
#include <stdint.h>

class Collidable {
 protected:
  uint8_t type_ = 0;
 public:
  uint8_t type() { return type_; }
};


#endif //OVERLORD_COLLIDABLE_H
