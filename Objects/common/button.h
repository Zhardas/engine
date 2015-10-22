class Button;
#ifndef ENGINE_OBJECTS_COMMON_BUTTON_H_
#define ENGINE_OBJECTS_COMMON_BUTTON_H_
#include <Objects/interfaces/interactive.h>
#include <Objects/interfaces/complex.h>
#include <Objects/textured_quad.h>
#include <Objects/text.h>

class Button: public Complex, public Interactive {
 private:
 public:
  TexturedQuad* background_ = nullptr;
  Text* text_ = nullptr;

  Button();
  ~Button();
  virtual Size size();
  virtual void set_size(float width, float height);
  virtual Position position();
  virtual void set_position(float x, float y);
  virtual void set_visible(bool visible);
  void AlignText();
  void set_text(std::string text);
};

#endif  // ENGINE_OBJECTS_COMMON_BUTTON_H_
