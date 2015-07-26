#include "Text.h"

Text::Text(std::string font, int size, bool bold, bool italic) {
    Text::font = new Font(font, size, bold, italic);
}

void Text::SetSize() {
    Size calc_size = font->GetSize(text);
    size.height = calc_size.height;
    size.width = calc_size.width;
}
