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
  text_ = new Text("Arial", 24, false, false);
  set_size(256.0f, 64.0f);
  set_texture("white.png");
  text_->color_green_ = 0;
  text_->color_red_ = 0;
  text_->color_blue_ = 0;
  Add(text_);
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
