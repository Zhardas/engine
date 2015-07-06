class Text;
#ifndef PLAYGROUND_TEXT_H
#define PLAYGROUND_TEXT_H

#include <Graphics/Font.h>
#include "Game.h"

class Text {
private:
    std::string text;
    Size* position;
    Size* size;
public:
    byte Alpha = 255, Red = 255, Green = 255, Blue = 255;
    Text(std::string font, int size, bool bold, bool italic);
    Font* font;
    void SetText(std::string text){this->text = text;};
    std::string GetText(){return text;}
    Size* GetPosition() const{return position;}
    void SetPosition(Size *position){
        delete Text::position;
        Text::position = position;
    }
    Size *GetSize() const {
        return size;
    }
    void SetSize(Size *size) {
        delete Text::size;
        Text::size = size;
    }
};


#endif //PLAYGROUND_TEXT_H
