#include "./button.h"

Size Button::size() {
  return background_->size();
}
void Button::set_size(float width, float height) {
  background_->set_size(width, height);
  AlignText();
}
Position Button::position() {
  return background_->position();
}
void Button::set_position(float x, float y) {
  background_->set_position(x, y);
  AlignText();
}
void Button::set_visible(bool visible) {
  visible_ = visible;
}
Button::Button() {
  text_ = new Text("Arial", 24, false, false);
  background_ = new TexturedQuad();
  background_->set_size(256.0f, 64.0f);
  AlignText();
  complex_list_.push_back(background_);
  complex_list_.push_back(text_);
}
Button::~Button() {

}
void Button::AlignText() {
  auto x_mod = background_->size().width - text_->size().width;
  auto y_mod = background_->size().height - text_->size().height;
  text_->set_position(background_->position().x + x_mod / 2, background_->position().y + y_mod / 3);
}
void Button::set_text(std::string text) {
  text_->set_text(text);
  AlignText();
}
