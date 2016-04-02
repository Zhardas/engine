class Checkbox;

#ifndef OBJECTS_COMMON_CHECKBOX_H_
#define OBJECTS_COMMON_CHECKBOX_H_
#include <objects/textured_quad.h>

class Checkbox: public TexturedQuad {
 private:
  bool checked_ = false;
 public:
  TexturedQuad *tick_ = nullptr;

  Checkbox();
  virtual void set_size(float width, float height);
  virtual void set_position(float x, float y);
  bool checked() { return checked_; }
  void set_checked(bool checked) {
    checked_ = checked;
    tick_->set_visible(checked_);
  }
};

#endif  // OBJECTS_COMMON_CHECKBOX_H_
