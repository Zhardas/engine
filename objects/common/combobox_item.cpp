#include "combobox_item.h"

ComboboxItem::ComboboxItem(const std::string &text) {
  text_->set_text(text);
  Add(text_);
  text_->color_red_ = 0;
  text_->color_green_ = 0;
  text_->color_blue_ = 0;
  set_texture("white.png");
  set_size(87.0f, 17.0f);
}
void ComboboxItem::set_position(float x, float y) {
  TexturedQuad::set_position(x, y);
  text_->set_position(position_.x, position_.y);
}
void ComboboxItem::set_size(float width, float height) {
  TexturedQuad::set_size(width, height);
  text_->set_position(position_.x, position_.y);
}
void ComboboxItem::set_text(const std::string &text) {
  text_->set_text(text);
}
void ComboboxItem::set_visible(bool visible) {
  TexturedQuad::set_visible(visible);
  text_->set_visible(visible);
}