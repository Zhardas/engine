#ifndef OVERLORD_CONSOLE_H
#define OVERLORD_CONSOLE_H

#include <objects/textured_quad.h>
#define TEXTBOX_HEIGHT 25.0f

class Console {
 private:
  TexturedQuad* background_;
  TexturedQuad* textbox_;
  std::list<Text*> text_list_;
  Text* text_;
 public:
  Console();
  ~Console();

  void Add(DrawableLayer *drawable_layer, TextLayer *text_layer);
};


#endif //OVERLORD_CONSOLE_H
