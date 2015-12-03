class Button;
#ifndef ENGINE_OBJECTS_COMMON_BUTTON_H_
#define ENGINE_OBJECTS_COMMON_BUTTON_H_
#include <objects/interfaces/interactive.h>
#include <objects/interfaces/complex.h>
#include <objects/textured_quad.h>
#include <objects/text.h>

class Button: public Complex, public Interactive {
 private:
 public:
  std::unique_ptr<TexturedQuad> background_;
  std::unique_ptr<Text> text_;

  Button();
  virtual Size size();
  virtual void set_size(float width, float height);
  virtual Position position();
  virtual void set_position(float x, float y);
  virtual void set_visible(bool visible);
  void AlignText();
  void set_text(std::string text);
};

#endif  // ENGINE_OBJECTS_COMMON_BUTTON_H_
