class Font;
#ifndef PLAYGROUND_FONT_H
#define PLAYGROUND_FONT_H
#include "game.h"
#include "helper/types.h"

class Font {
private:
    ID3DXFont *font_;
public:
    Font(std::string facename, int height, bool bold, bool italic);
    ~Font();

    ID3DXFont *font() const {
        return font_;
    }

    Size size(std::string text){
        RECT rcRect = {0, 0, 0, 0};
        // calculate required rect
        font_->DrawText(NULL, text.c_str(), text.length(), &rcRect, DT_CALCRECT,
                        D3DCOLOR_XRGB(0, 0, 0));

        // return size
        return Size(rcRect.right - rcRect.left, rcRect.bottom - rcRect.top);
    }
};


#endif //PLAYGROUND_FONT_H
