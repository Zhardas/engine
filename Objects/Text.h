class Text;

#ifndef PLAYGROUND_TEXT_H
#define PLAYGROUND_TEXT_H

#include "game.h"
#include "graphics/font.h"
#include "objects/drawable.h"

class Text: public Drawable {
 private:
  std::string text_;
 public:
  byte color_alpha_ = 255;
  byte color_red_ = 255;
  byte color_green_ = 255;
  byte color_blue_ = 255;
  Font *font_;
  bool reset_size_ = true;

  Text(std::string font, int size, bool bold, bool italic);
  ~Text();

  virtual void set_visible(bool visible){
    visible_ = visible;
  }
  void set_text(std::string text) {
    this->text_ = text;
    if (reset_size_)reset_size();
  };

  std::string text() { return text_; }

  Position position() { return position_; }

  Size size() {
    return size_;
  }

  void reset_size();

  void set_size(float width, float height) {
    size_.width = width;
    size_.height = height;
  }
  void set_position(Position position) {
    Drawable::set_position(position);
  }
  void set_size(Size size) {
    Drawable::set_size(size);
  }
  void set_position(float x, float y) {
    position_.x = x;
    position_.y = y;
  }
};
#endif //PLAYGROUND_TEXT_H
