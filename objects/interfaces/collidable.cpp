#include "Collidable.h"
Collidable::Collidable() {

}
void Collidable::Collide(const Collidable &collidable) {
  for (auto collision : collision_callbacks_) {
    collision(collidable);
  }
}