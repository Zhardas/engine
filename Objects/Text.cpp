#include "text.h"

Text::Text(std::string font, int size, bool bold, bool italic) {
  font_ = new Font(font, size, bold, italic);
}

void Text::reset_size() {
  Size calc_size = font_->size(text_);
  size_.height = calc_size.height;
  size_.width = calc_size.width;
}

Text::~Text(){
  delete font_;
};
void Text::set_position(float x, float y) {
  position_.x = x;
  position_.y = Game::instance()->height() - y - size_.height;
}
void Text::set_size(Size size) {
  position_.y -= size_.height;
  Drawable::set_size(size);
  position_.y += size_.height;
}
