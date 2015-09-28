#ifndef OVERLORD_CONSOLE_H
#define OVERLORD_CONSOLE_H

#include <objects/textured_quad.h>
#include <objects/interfaces/interactive.h>
#include <objects/text.h>
#include <objects/interfaces/complex.h>
#define TEXTBOX_HEIGHT 25.0f

class Console: public Complex, public Interactive {
 private:
  bool visible_;
  TexturedQuad *background_;
  TexturedQuad *textbox_;
//  std::list<Text*> text_list_;
  Text *text_;
 public:
  Console();
  ~Console();

  void set_visible(bool visible) {
    visible_ = visible;
    background_->visible_ = false;
    textbox_->visible_ = false;
    text_->visible_ = false;

  }
  bool visible() { return visible_; }
  void Add(std::list<Drawable *> &list) {
    list.push_back(background_);
    list.push_back(textbox_);
    list.push_back(text_);
  }
  virtual void Remove(std::list<Drawable *> &list) {
    list.remove(background_);
    list.remove(textbox_);
    list.remove(text_);
  }
};


#endif //OVERLORD_CONSOLE_H
