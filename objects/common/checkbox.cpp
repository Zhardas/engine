#include "./checkbox.h"

void Checkbox::set_size(float width, float height) {
  TexturedQuad::set_size(width, height);
  tick_->set_size(width, height);
}
void Checkbox::set_position(float x, float y) {
  TexturedQuad::set_position(x, y);
  tick_->set_position(x, y);
}
Checkbox::Checkbox() {
  tick_ = new TexturedQuad();
  tick_->set_texture("checkbox_tick.png");
  tick_->set_visible(checked_);
  set_size(13.0f, 13.0f);
  set_texture("checkbox.png");
  Add(tick_);

  events_mouse_up_.push_back([this](const uint8_t &button, const Position &pos) {
    if (button == 0 && Contains(pos) && visible_) {
      checked_ = !checked_;
      tick_->set_visible(checked_);
      return true;
    }
    return false;
  });
}
