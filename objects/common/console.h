class Console;

#ifndef OBJECTS_COMMON_CONSOLE_H_
#define OBJECTS_COMMON_CONSOLE_H_

#include <memory>
#include "objects/textured_quad.h"
#include "objects/text.h"
#include "textbox.h"

#define TEXTBOX_HEIGHT 25.0f

class Console: public TexturedQuad {
 private:
  const uint8_t font_size = 16;
  std::shared_ptr<TextBox> textbox_ = std::make_shared<TextBox>("Consolas", font_size, false, false);

 public:
  Console();

  static std::shared_ptr<Console> instance() {
    static std::shared_ptr<Console> instance;
    if (!instance) {
      instance = std::make_shared<Console>();
    }
    return instance;
  }

  void set_visible(bool visible) { visible_ = visible; }
  bool visible() { return visible_; }
};


#endif // OBJECTS_COMMON_CONSOLE_H_
