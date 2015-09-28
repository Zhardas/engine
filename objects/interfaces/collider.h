class Collider;
#ifndef HEADACHE_COLLIDER_H
#define HEADACHE_COLLIDER_H

#include <string>
#include <list>
#include <functional>
#include "./collidable.h"

class Collider {
 private:
 public:
  std::list<std::function<void(const Collidable &)>> events_collision_ = {};

  void Collide(Collidable* collidable){
    for (auto collision : events_collision_) {
      collision(*collidable);
    }
  }
};


#endif // HEADACHE_COLLIDER_H
