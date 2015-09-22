class Drawable;

#ifndef HEADACHE_DRAWABLE_H
#define HEADACHE_DRAWABLE_H

#include <string>
#include <list>
#include <functional>
#include "Helper/types.h"

class Drawable {
 private:
 protected:
  SizeF size_ = SizeF(32.0f, 32.0f);
  SizeF size_scaled = SizeF(32.0f, 32.0f);
  Position position_ = Position(0, 0);
  SizeF scale_ = SizeF(1.0f, 1.0f);
  float rotation_ = 0.0f;
 public:
  Drawable();

  virtual SizeF size() = 0;

  virtual void set_size(SizeF size) = 0;

  virtual Position position() = 0;

  virtual void set_position(Position position) = 0;

  virtual void set_position(float x, float y) = 0;

  virtual SizeF scale() { return scale_; }

  virtual void set_scaled_size(SizeF scale) {
    scale_.width = scale.width;
    scale_.height = scale.height;
    size_scaled.width = size_.width * scale.width;
    size_scaled.height = size_.width * scale.height;

  }

  virtual SizeF scaled_size() { return size_scaled; }

  virtual void set_rotation(float rot) {
    rotation_ = rot;
  }

  virtual float rotation() {
    return rotation_;
  }

  virtual bool Contains(Position pos) {
    return pos.x >= position().x - (size_scaled.width - size_.width) / 2 &&
        pos.x <= position().x + size_.width + (size_scaled.width - size_.width) / 2 &&
        pos.y >= position().y - (size_scaled.height - size_.height) / 2 &&
        pos.y <= position().y + size_.height + (size_scaled.height - size_.height) / 2;
  }
};


#endif //HEADACHE_DRAWABLE_H
