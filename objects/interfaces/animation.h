class Animation;
#ifndef OVERLORD_ANIMATION_H
#define OVERLORD_ANIMATION_H
#include <stdint.h>
#include <string>
#include <objects/drawable.h>
#include <sstream>
#include "updatable.h"

class Animation: public Updatable {
 private:
  std::string *texture_pointer_ = nullptr;
  unsigned int timer = 0;
 public:
  std::string texture_base_ = "default";
  unsigned int texture_index_start_ = 0;
  unsigned int texture_index_end_ = 1;
  unsigned int texture_index_current_ = 0;
  unsigned int animation_speed_ = 5;

  void InitAnimation(std::string *texture_pointer, std::string texture_base) {
    texture_pointer_ = texture_pointer;
    texture_base_ = texture_base;
  }

  virtual void Update() {
    timer = (timer + 1) % animation_speed_;
    if (timer == 0) {
      texture_index_current_ = (texture_index_current_ + 1) % (texture_index_end_+1);
      if (texture_index_current_ == 0)texture_index_current_ = texture_index_start_;
      std::stringstream ss;
      ss << texture_base_ << texture_index_current_ << ".png";
      *texture_pointer_ = ss.str();
    }
  }
};

#endif //OVERLORD_ANIMATION_H