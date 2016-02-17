class Button;
#ifndef OBJECTS_COMMON_BUTTON_H_
#define OBJECTS_COMMON_BUTTON_H_
#include <objects/textured_quad.h>
#include <objects/text.h>

class Button: public TexturedQuad {
 private:
 public:
  std::shared_ptr<Text> text_ = std::make_shared<Text>("Arial", 24, false, false);

  Button();
  virtual void set_size(float width, float height);
  virtual void set_position(float x, float y);
  void AlignText();
  void set_text(std::string text);
};

#endif  // OBJECTS_COMMON_BUTTON_H_
