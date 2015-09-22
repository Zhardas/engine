class Collidable;
#ifndef OVERLORD_COLLIDABLE_H
#define OVERLORD_COLLIDABLE_H

#include <string>
#include <list>
#include <functional>
#include "./collidable.h"

class Collidable {
 private:
 public:
  std::string type_ = "drawable";
  std::list<std::function<void(const Collidable &)>> collision_callbacks_;

  Collidable();

  virtual void Collide(const Collidable &drawable);
};


#endif //OVERLORD_COLLIDABLE_H
