#include "Text.h"

Text::Text(std::string font, int size) {
    Text::font = new Font(font,size);
}
