class Font;
#ifndef PLAYGROUND_FONT_H
#define PLAYGROUND_FONT_H
#include "game.h"
#include "helper/types.h"

class Font {
 private:
  ID3DXFont *font_ = nullptr;
 public:
  Font(std::string facename, int height, bool bold, bool italic);
  ~Font();

  Size size(std::string text);

  ID3DXFont *font() const {
    return font_;
  }
};


#endif //PLAYGROUND_FONT_H
