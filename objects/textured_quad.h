class TexturedQuad;

#ifndef OBJECTS_TEXTURED_QUAD_H_
#define OBJECTS_TEXTURED_QUAD_H_

#include <string>
#include <functional>
#include "./drawable.h"
#include "../game.h"

class TexturedQuad: public Drawable {
 private:
  unsigned int animation_timer_ = 0;
  void CalcScaling();

 protected:
  std::string texture_ = "default.png";

 public:
  TexturedQuad() { }

  // Animation
  bool animated_ = false;
  std::string texture_base_ = "default";
  uint16_t texture_index_start_ = 0;
  uint16_t texture_index_end_ = 1;
  uint16_t texture_index_current_ = 0;
  uint16_t animation_speed_ = 5;

  virtual void Update();

  // Generic
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

  bool Contains(const Position &pos) {
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

  // Rendering
  void Draw(Renderer *renderer, uint32_t *index);
  void PrepareVertices(Renderer *renderer, v_3ct *vertices, uint32_t *index);
};


#endif // OBJECTS_TEXTURED_QUAD_H_
