class Text;

#ifndef PLAYGROUND_TEXT_H
#define PLAYGROUND_TEXT_H

#include <Graphics/Font.h>
#include "Game.h"

class Text {
private:
    std::string text;
    Position position;
    Size size;
public:
    byte Alpha = 255, Red = 255, Green = 255, Blue = 255;

    Text(std::string font, int size, bool bold, bool italic);

    Font *font;

    void SetText(std::string text) { this->text = text; };

    std::string GetText() { return text; }

    Position GetPosition() { return position; }

    void SetPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }

    void SetPosition(Position size) {
        position.x = size.x;
        position.y = size.y;
    }

    Size GetSize() const {
        return size;
    }

    void SetSize(Size size) {
        this->size.height = size.height;
        this->size.width = size.width;
    }

    void SetSize();
};


#endif //PLAYGROUND_TEXT_H
