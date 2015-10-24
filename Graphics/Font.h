class Font;
#ifndef PLAYGROUND_FONT_H
#define PLAYGROUND_FONT_H
#include "game.h"
#include "helper/types.h"

class Font {
 private:
  removable_unique_ptr <ID3DXFont> font_;
 public:
  Font(std::string facename, int height, bool bold, bool italic);

  Size size(std::string text);

  ID3DXFont *font() const {
    return font_.get();
  }
};


#endif //PLAYGROUND_FONT_H
