#include "./checkbox.h"

void Checkbox::set_size(float width, float height) {
  TexturedQuad::set_size(width, height);
  tick_->set_size(width, height);
}
void Checkbox::set_position(float x, float y) {
  TexturedQuad::set_position(x, y);
  tick_->set_position(x,y);
}
Checkbox::Checkbox() {
  tick_ = new TexturedQuad();
  tick_->set_texture("tick.png");
  tick_->set_visible(checked_);
  set_size(32.0f, 32.0f);
  set_texture("white.png");
  Add(tick_);

  events_mouse_up_.push_back([this](const uint8_t &button, const Position &pos) {
    if (button == 0 && Contains(pos)) {
      checked_ = !checked_;
      tick_->set_visible(checked_);
    }
    return false;
  });
}
