class Font;
#ifndef PLAYGROUND_TEXTMANAGER_H
#define PLAYGROUND_TEXTMANAGER_H
#include "Game.h"

class Font {
private:
    ID3DXFont * g_font;
public:
    Font(std::string facename, int height, bool bold, bool italic);
    ~Font();

    ID3DXFont *GetFont() const {
        return g_font;
    }
};


#endif //PLAYGROUND_TEXTMANAGER_H