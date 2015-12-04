class TexturedQuad;

#ifndef HEADACHE_STATICDRAWABLE_H
#define HEADACHE_STATICDRAWABLE_H

#include "drawable.h"
#include "game.h"
#include <string>
#include <functional>

class TexturedQuad: public Drawable {
 private:
  void CalcScaling();
 protected:
  std::string texture_ = "default.png";

 public:
  TexturedQuad();

  void set_texture(std::string texture) {
    texture_ = texture;
  }

  std::string texture() {
    return texture_;
  }

  Size size() {
    return size_;
  }

  void set_size(Size size) {
    Drawable::set_size(size);
  }

  Position position() {
    return position_;
  }

  void set_position(Position position) {
    Drawable::set_position(position);
  }

  Size scale() {
    return scale_;
  }

  void set_scale(Size scale) {
    scale_.width = scale.width;
    scale_.height = scale.height;
    CalcScaling();
  }

  Size scaled_size() {
    return size_scaled;
  }

  void set_rotation(float rot) {
    Drawable::set_rotation(rot);
  }

  float rotation() {
    return Drawable::rotation();
  }

  bool Contains(Position &pos) {
    return Drawable::Contains(pos);
  }

  void set_color(int index, DWORD argb) {
    color_[index] = argb;
  }
  void set_color(DWORD argb) {
    color_[0] = argb;
    color_[1] = argb;
    color_[2] = argb;
    color_[3] = argb;
  }
  virtual void set_size(float width, float height) {
    size_.width = width;
    size_.height = height;
    CalcScaling();
  }
  virtual void set_position(float x, float y) {
    position_.x = x;
    position_.y = y;
  }
  virtual void set_visible(bool visible) {
    visible_ = visible;
  }
  DWORD color_[4] = {
      0xffffffff,
      0xffffffff,
      0xffffffff,
      0xffffffff
  };
};


#endif //HEADACHE_STATICDRAWABLE_H
