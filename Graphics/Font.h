class Font;
#ifndef PLAYGROUND_FONT_H
#define PLAYGROUND_FONT_H
#include "Game.h"
#include "Objects/Text.h"

class Font {
private:
    ID3DXFont * g_font;
public:
    Font(std::string facename, int height, bool bold, bool italic);
    ~Font();

    ID3DXFont *GetFont() const {
        return g_font;
    }

    Size GetSize(std::string text){
        RECT rcRect = {0, 0, 0, 0};
        // calculate required rect
        g_font->DrawText(NULL, text.c_str(), text.length(), &rcRect, DT_CALCRECT,
                    D3DCOLOR_XRGB(0, 0, 0));

        // return size
        return Size(rcRect.right - rcRect.left, rcRect.bottom - rcRect.top);
    }
};


#endif //PLAYGROUND_FONT_H
