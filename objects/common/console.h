#ifndef OVERLORD_CONSOLE_H
#define OVERLORD_CONSOLE_H

#include <objects/textured_quad.h>
#define TEXTBOX_HEIGHT 25.0f

class Console {
 private:
  bool visible_;
  TexturedQuad* background_;
  TexturedQuad* textbox_;
  std::list<Text*> text_list_;
  Text* text_;
 public:
  Console();
  ~Console();

  void Add(DrawableLayer *drawable_layer, TextLayer *text_layer);
  void set_visible(bool visible) {
    visible_ = visible;
    background_->visible_ = false;
    textbox_->visible_ = false;
    text_->visible_ = false;

  }
  bool visible(){return visible_; }
};


#endif //OVERLORD_CONSOLE_H
