class Drawable;

#ifndef OBJECTS_DRAWABLE_H_
#define OBJECTS_DRAWABLE_H_

#include <string>
#include <list>
#include <functional>
#include "Helper/types.h"

class Drawable {
 protected:
  Size size_ = Size(32.0f, 32.0f);
  Size size_scaled = Size(32.0f, 32.0f);
  Position position_ = Position(0, 0);
  Size scale_ = Size(1.0f, 1.0f);
  float rotation_ = 0.0f;
  bool visible_ = true;

 public:
  Drawable();

  virtual Size size() = 0;

  virtual void set_size(Size size) {
    set_size(size.width, size.height);
  }

  virtual void set_size(float width, float height) = 0;

  virtual Position position() = 0;

  virtual void set_position(Position position) {
    set_position(position.x, position.y);
  }

  virtual void set_position(float x, float y) = 0;

  virtual void set_scale(Size scale) {
    scale_.width = scale.width;
    scale_.height = scale.height;
    size_scaled.width = size_.width * scale.width;
    size_scaled.height = size_.width * scale.height;
  }
  virtual Size scale() { return scale_; }

  virtual Size scaled_size() { return size_scaled; }

  virtual void set_rotation(float rot) {
    rotation_ = rot;
  }

  virtual float rotation() {
    return rotation_;
  }

  virtual bool visible() { return visible_; }
  virtual void set_visible(bool visible) = 0;

  virtual bool Contains(const Position &pos) {
    // TODO(Zhardas): Take scaling and rotation into account.
    return pos.x >= position().x &&
        pos.x <= position().x + size().width &&
        pos.y >= position().y &&
        pos.y <= position().y + size().height;
  }
  virtual void Update(){}
};

#endif  // OBJECTS_DRAWABLE_H_
