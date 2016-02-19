#include "drawable.h"

Drawable::Drawable() {

}
void Drawable::Collide(Drawable* collidable) {
  for (auto collision : events_collision_) {
    collision(collidable);
  }
}
void Drawable::Add(Drawable* drawable) {
  drawable->set_reload_ptr(reload_layer_);
  complex_list_.push_back(std::unique_ptr<Drawable>(drawable));
  is_complex_ = true;
  if (reload_layer_ != nullptr)*reload_layer_ = true;
}
void Drawable::Remove(Drawable* drawable) {
  complex_list_.remove_if([drawable](const auto &ptr){
    return ptr.get() == drawable;
  });
  if (reload_layer_ != nullptr)*reload_layer_ = true;
  if (complex_list_.size() == 0)is_complex_ = false;
}
bool Drawable::MouseUp(const uint8_t &parameter, const Position &position) {
  for (auto func : events_mouse_up_) {
    if (func(parameter, position))return true;
  }
  return false;
}
bool Drawable::MouseDown(const uint8_t &parameter, const Position &position) {
  for (auto func : events_mouse_down_) {
    if (func(parameter, position))return true;
  }
  return false;
}
bool Drawable::MouseMove(const Position &position) {
  for (auto func : events_mouse_move_) {
    if (func(position))return true;
  }
  return false;
}
bool Drawable::KeyUp(const uint8_t &parameter) {
  for (auto func : events_key_up_) {
    if (func(parameter))return true;
  }
  return false;
}
bool Drawable::KeyDown(const uint8_t &parameter) {
  for (auto func : events_key_down_) {
    if (func(parameter))return true;
  }
  return false;
}
void Drawable::set_size(Size size) {
  set_size(size.width, size.height);
}
void Drawable::set_position(Position position) {
  set_position(position.x, position.y);
}
void Drawable::set_scale(Size scale) {
  scale_.width = scale.width;
  scale_.height = scale.height;
  size_scaled.width = size_.width * scale.width;
  size_scaled.height = size_.width * scale.height;
}
Size Drawable::scaled_size() { return size_scaled; }
Size Drawable::scale() { return scale_; }
void Drawable::set_rotation(float rot) {
  rotation_ = rot;
}
float Drawable::rotation() {
  return rotation_;
}
bool  Drawable::visible() { return visible_; }
void Drawable::set_visible(bool visible) { visible_ = visible; }
bool Drawable::Contains(const Position &pos) {
  // TODO(Zhardas): Take scaling and rotation into account.
  return pos.x >= position().x &&
      pos.x <= position().x + size().width &&
      pos.y >= position().y &&
      pos.y <= position().y + size().height;
}
void Drawable::Update() {
  if (!is_complex_)return;
  for (const auto &obj : complex_list_) {
    obj->Update();
  }
  complex_list_.remove_if([](const auto &ptr){
    return ptr->remove_;
  });
}
void Drawable::set_reload_ptr(bool *ptr) {
  reload_layer_ = ptr;
  if (is_complex_) {
    for (const auto &obj : complex_list_) {
      obj.get()->set_reload_ptr(ptr);
    }
  }
}
