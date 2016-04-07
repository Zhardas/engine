class Button;
#ifndef OBJECTS_COMMON_BUTTON_H_
#define OBJECTS_COMMON_BUTTON_H_
#include <objects/textured_quad.h>
#include <objects/text.h>

class Button: public TexturedQuad {
 private:
 public:
  Text* text_ = nullptr;

  std::list<std::function<void()>> events_onclick_ = {};

  Button();
  virtual void set_size(float width, float height);
  virtual void set_position(float x, float y);
  void AlignText();
  void set_text(std::string text);
  void Click();
};

#endif  // OBJECTS_COMMON_BUTTON_H_
