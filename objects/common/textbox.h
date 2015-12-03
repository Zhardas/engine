class TextBox;
#ifndef ENGINE_OBJECTS_COMMON_TEXTBOX_H_
#define ENGINE_OBJECTS_COMMON_TEXTBOX_H_
#include "objects/textured_quad.h"
#include "objects/text.h"
#include "objects/interfaces/complex.h"
#include "objects/interfaces/interactive.h"

class TextBox: public Complex, public Interactive {
 private:
 public:
  std::unique_ptr<TexturedQuad> background_ ;
  std::unique_ptr<Text> text_;
  bool is_active_ = false;

  TextBox(std::string font = "Consolas", uint8_t font_size = 28, bool bold = false, bool italic = false);
  virtual Size size();
  virtual void set_size(float width, float height);
  virtual Position position();
  virtual void set_position(float x, float y);
  virtual void set_visible(bool visible);
  void AlignText();
};


#endif  // ENGINE_OBJECTS_COMMON_TEXTBOX_H_
