#include "textbox.h"

TextBox::TextBox(std::string font, uint8_t font_size, bool bold, bool italic) {
  background_ = std::make_unique<TexturedQuad>();
  background_->set_texture("textbox.png");
  background_->set_size(128.0f, 32.0f);
  text_ = std::make_unique<Text>(font, font_size, bold, italic);
  text_->color_blue_ = 0;
  text_->color_red_ = 0;
  text_->color_green_ = 0;
  AlignText();
  events_mouse_up_.push_back([this](const uint8_t &button, Position *pos) {
    if (button == 0) {
      if (background_->Contains(*pos)) {
        is_active_ = true;
        return true;
      } else {
        is_active_ = false;
        return false;
      }
    }
    return false;
  });
  events_key_down_.push_back([&](const uint8_t &key) {
    if (!is_active_)return false;
    if (key == VK_BACK) {
      if (text_->text().length() > 0) {
        text_->set_text(text_->text().substr(0, text_->text().length() - 1));
        return true;
      }
    } else if (key >= 32 && key <= 126) {
      std::stringstream ss;
      ss << text_->text() << key;
      text_->set_text(ss.str());
      return true;
    }
    return false;
  });
  complex_list_.push_back(background_.get());
  complex_list_.push_back(text_.get());
}
Size TextBox::size() {
  return background_->size();
}
void TextBox::set_size(float width, float height) {
  background_->set_size(width, height);
  AlignText();
}
Position TextBox::position() {
  return background_->position();
}
void TextBox::set_position(float x, float y) {
  background_->set_position(x, y);
  AlignText();
}
void TextBox::set_visible(bool visible) {
  visible_ = visible;
}
void TextBox::AlignText() {
  auto y_mod = background_->size().height - text_->size().height;
  text_->set_position(background_->position().x + 5.0f, background_->position().y + y_mod / 3);
}
