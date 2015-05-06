class TexturedQuad;
#ifndef HEADACHE_STATICDRAWABLE_H
#define HEADACHE_STATICDRAWABLE_H

#include "Drawable.h"
#include <Game.h>
#include <string>
#include <functional>

class TexturedQuad : Drawable{
private:
    std::string d_texture;
public:
    TexturedQuad();
    void SetTexture(std::string texture);
    std::string GetTexture();
    Size* GetSize();
    void SetSize(Size * /* new GetSize */);
    void SetSize(int width, int height);
    Position* GetPosition();
    void SetPosition(Position * /* new GetPosition */);
    void SetPosition(int x, int y);

    std::function<void (const uint8_t&, Position*)> OnMouseUp;
    std::function<void (const uint8_t&, Position*)> OnMouseDown;
    std::function<void (Position*)> OnMouseMove;
    std::function<void (const uint8_t&)> OnKeyUp;
    std::function<void (const uint8_t&)> OnKeyDown;
};


#endif //HEADACHE_STATICDRAWABLE_H
