#include "./button.h"

void Button::set_size(float width, float height) {
  TexturedQuad::set_size(width, height);
  AlignText();
}
void Button::set_position(float x, float y) {
  TexturedQuad::set_position(x, y);
  AlignText();
}
Button::Button() {
  text_ = new Text();
  set_size(102.0f, 26.0f);
  set_texture("button.png");
  Add(text_);

  events_mouse_up_.push_back([this](const uint8_t &mbutton, const Position &pos) {
    if (mbutton == 0 && Contains(pos) && visible_) {
      Click();
      return true;
    }
    return false;
  });
}
void Button::AlignText() {
  auto x_mod = size().width - text_->size().width;
  auto y_mod = size().height - text_->size().height;
  text_->set_position(position().x + x_mod / 2, position().y + y_mod / 3);
}
void Button::set_text(std::string text) {
  text_->set_text(text);
  AlignText();
}
void Button::Click() {
  for (const auto &f : events_onclick_) {
    f();
  }
}

