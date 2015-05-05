class TexturedQuad;
#ifndef HEADACHE_STATICDRAWABLE_H
#define HEADACHE_STATICDRAWABLE_H

#include "Drawable.h"
#include <string>
#include <c++/functional>

class TexturedQuad : Drawable{
private:
    std::string _texture = "default.png";
public:
    TexturedQuad();
    void SetTexture(std::string texture);
    std::string GetTexture();
    Size size();
    void set_size(Size* /* new size */);
    Position position();
    void set_position(Position* /* new position */);

    std::function<void (const uint8_t&, Position*)> OnMouseUp;
    std::function<void (const uint8_t&, Position*)> OnMouseDown;
    std::function<void (const uint8_t&)> OnKeyUp;
    std::function<void (const uint8_t&)> OnKeyDown;
};


#endif //HEADACHE_STATICDRAWABLE_H
