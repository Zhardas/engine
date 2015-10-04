class Animation;
#ifndef OVERLORD_ANIMATION_H
#define OVERLORD_ANIMATION_H
#include <stdint.h>
#include <string>
#include <objects/drawable.h>
#include <sstream>
#include "updatable.h"
#include "../textured_quad.h"

class Animation: public TexturedQuad, public Updatable {
 private:
  unsigned int timer_ = 0;
 public:
  std::string texture_base_ = "default";
  unsigned int texture_index_start_ = 0;
  unsigned int texture_index_end_ = 1;
  unsigned int texture_index_current_ = 0;
  unsigned int animation_speed_ = 5;

  virtual void Update() {
    timer_ = (timer_ + 1) % animation_speed_;
    if (timer_ == 0) {
      texture_index_current_ = (texture_index_current_ + 1) % (texture_index_end_+1);
      if (texture_index_current_ == 0)texture_index_current_ = texture_index_start_;
      texture_ = texture_base_ + std::to_string(texture_index_current_) + ".png";
    }
  }
};

#endif //OVERLORD_ANIMATION_H