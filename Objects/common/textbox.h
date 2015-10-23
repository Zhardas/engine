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
  TexturedQuad* background_ = nullptr;
  Text* text_ = nullptr;
  bool is_active_ = false;

  TextBox();
  ~TextBox();
  virtual Size size();
  virtual void set_size(float width, float height);
  virtual Position position();
  virtual void set_position(float x, float y);
  virtual void set_visible(bool visible);
  void AlignText();
};


#endif  // ENGINE_OBJECTS_COMMON_TEXTBOX_H_
