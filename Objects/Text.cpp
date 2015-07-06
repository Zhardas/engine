#include "Text.h"

Text::Text(std::string font, int size, bool bold, bool italic) {
    Text::font = new Font(font,size,bold, italic);
}
