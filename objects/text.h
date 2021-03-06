class Text;

#ifndef OBJECTS_TEXT_H_
#define OBJECTS_TEXT_H_

#include <string>
#include <memory>
#include "./game.h"
#include "graphics/font.h"
#include "objects/drawable.h"

class Text: public Drawable {
 private:
  std::string text_ = "";

 public:
  byte color_alpha_ = 255;
  byte color_red_ = 0;
  byte color_green_ = 0;
  byte color_blue_ = 0;
  std::unique_ptr<Font> font_;
  bool reset_size_ = true;

  Text(std::string font = "Segoe UI", int size = 18, bool bold = false, bool italic = false);

  void set_text(std::string text) {
    this->text_ = text;
    if (reset_size_)reset_size();
  }
  std::string text() { return text_; }
  Position position() { return position_; }
  Size size() { return size_; }

  void reset_size();

  void set_size(float width, float height) {
    size_.width = width;
    size_.height = height;
  }
  void set_position(Position position) {
    set_position(position.x, position.y);
  }
  void set_size(Size size);
  void set_position(float x, float y);

  // Rendering
  void Draw(Renderer *renderer, uint32_t *index);
};
#endif  // OBJECTS_TEXT_H_
