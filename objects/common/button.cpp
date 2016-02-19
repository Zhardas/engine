#include "./button.h"

void Button::set_size(float width, float height) {
  Drawable::set_size(width, height);
  AlignText();
}
void Button::set_position(float x, float y) {
  Drawable::set_position(x, y);
  AlignText();
}
Button::Button() {
  set_size(256.0f, 64.0f);
  complex_list_.push_back(std::move(text_));
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
