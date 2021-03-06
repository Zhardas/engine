class TextBox;

#ifndef OBJECTS_COMMON_TEXTBOX_H_
#define OBJECTS_COMMON_TEXTBOX_H_
#include <string>
#include "objects/textured_quad.h"
#include "objects/text.h"

class TextBox: public TexturedQuad {
 private:
 public:
  Text *text_ = nullptr;
  bool is_active_ = false;
  bool is_editable = true;

  TextBox(std::string font = "Segoe UI", uint8_t font_size = 18, bool bold = false, bool italic = false);
  virtual void set_size(float width, float height);
  virtual void set_position(float x, float y);
  void AlignText();
};


#endif  // OBJECTS_COMMON_TEXTBOX_H_
