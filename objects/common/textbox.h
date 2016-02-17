class TextBox;

#ifndef OBJECTS_COMMON_TEXTBOX_H_
#define OBJECTS_COMMON_TEXTBOX_H_
#include "objects/textured_quad.h"
#include "objects/text.h"

class TextBox: public TexturedQuad {
 private:
 public:
  std::shared_ptr<Text> text_;
  bool is_active_ = false;

  TextBox(std::string font = "Consolas", uint8_t font_size = 28, bool bold = false, bool italic = false);
  virtual void set_size(float width, float height);
  virtual void set_position(float x, float y);
  void AlignText();
};


#endif  // OBJECTS_COMMON_TEXTBOX_H_
