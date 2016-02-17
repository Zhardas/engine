#include "text.h"

Text::Text(std::string font, int size, bool bold, bool italic) : font_(std::make_unique<Font>(font,
                                                                                              size,
                                                                                              bold,
                                                                                              italic)) {

}

void Text::reset_size() {
  Size calc_size = font_->size(text_);
  size_.height = calc_size.height;
  size_.width = calc_size.width;
}
void Text::set_position(float x, float y) {
  position_.x = x;
  position_.y = Game::instance()->height() - y - size_.height;
}
void Text::set_size(Size size) {
  position_.y -= size_.height;
  Drawable::set_size(size);
  position_.y += size_.height;
}
void Text::Draw(Renderer *renderer, uint32_t *index) {
  if (!visible())return;
  RECT rect = {(LONG) position().x, (LONG) position().y,
                                     (LONG) (position().x + size().width),
                                     (LONG) (position().y + size().height)};
  font_->font()->DrawText(NULL,
                                text().c_str(), -1,
                                &rect,
                                DT_CENTER,
                                D3DCOLOR_ARGB(color_alpha_, color_red_,
                                              color_green_,
                                              color_blue_));
}
