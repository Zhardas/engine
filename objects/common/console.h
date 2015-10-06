#ifndef OVERLORD_CONSOLE_H
#define OVERLORD_CONSOLE_H

#include <objects/textured_quad.h>
#include <objects/interfaces/interactive.h>
#include <objects/text.h>
#include <objects/interfaces/complex.h>
#define TEXTBOX_HEIGHT 25.0f

class Console: public Complex, public Interactive {
 private:
  TexturedQuad *background_ = nullptr;
  TexturedQuad *textbox_ = nullptr;
//  std::list<Text*> text_list_;
  Text *text_ = nullptr;
 public:
  Console();
  ~Console();

  static Console* instance(){
    static Console* instance = nullptr;
    if(instance == nullptr){
      instance = new Console();
    }
    return instance;
  }

  void set_visible(bool visible) {
    visible_ = visible;
  }
  bool visible() { return visible_; }
  Size size() {
    return background_->size();
  }
  virtual void set_size(float width, float height) { }
  Position position() {
    return background_->position();
  }
  virtual void set_position(float x, float y) { }
};


#endif //OVERLORD_CONSOLE_H
