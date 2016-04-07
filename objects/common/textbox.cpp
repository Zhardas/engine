#include "textbox.h"

TextBox::TextBox(std::string font, uint8_t font_size, bool bold, bool italic) {
  text_ = new Text(font, font_size, bold, italic);
  set_texture("textbox.png");
  set_size(128.0f, 32.0f);
  text_->color_blue_ = 0;
  text_->color_red_ = 0;
  text_->color_green_ = 0;
  events_mouse_up_.push_back([this](const uint8_t &button, const Position &pos) {
    if (button == 0) {
      if (Contains(pos)) {
        is_active_ = true;
        return true;
      } else {
        is_active_ = false;
        return false;
      }
    }
    return false;
  });
  events_key_down_.push_back([this](const uint8_t &key) {
    if (!is_active_ || !is_editable)return false;
    if (key == VK_BACK) {
      if (text_->text().length() > 0) {
        text_->set_text(text_->text().substr(0, text_->text().length() - 1));
        AlignText();
        return true;
      }
    } else {
      std::stringstream ss;
      ss << text_->text() << key;
      text_->set_text(ss.str());
      AlignText();
      return true;
    }
    return false;
  });
  Add(text_);
}
void TextBox::set_size(float width, float height) {
  TexturedQuad::set_size(width, height);
  AlignText();
}
void TextBox::set_position(float x, float y) {
  TexturedQuad::set_position(x, y);
  AlignText();
}
void TextBox::AlignText() {
  auto y_mod = size().height - text_->size().height;
  text_->set_position(position().x + 5.0f, position().y + y_mod / 3);
}
