class Text;

#ifndef PLAYGROUND_TEXT_H
#define PLAYGROUND_TEXT_H

#include "graphics/font.h"
#include "game.h"

class Text {
 private:
  std::string text_;
  Position position_;
  Size size_;
 public:
  bool visible_ = true;
  byte color_alpha_ = 255;
  byte color_red_ = 255;
  byte color_green_ = 255;
  byte color_blue_ = 255;
  Font *font_;

  Text(std::string font, int size, bool bold, bool italic);


  void set_text(std::string text) { this->text_ = text; };

  std::string text() { return text_; }

  Position position() { return position_; }

  void set_position(int x, int y) {
    position_.x = x;
    position_.y = y;
  }
  Size size() const {
    return size_;
  }

  void set_size(int height, int width) {
    size_.height = height;
    size_.width = width;
  }

  void reset_size();
};


#endif //PLAYGROUND_TEXT_H
