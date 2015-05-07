class TexturedQuad;

#ifndef HEADACHE_STATICDRAWABLE_H
#define HEADACHE_STATICDRAWABLE_H

#include "Drawable.h"
#include <Game.h>
#include <string>
#include <functional>

class TexturedQuad : Drawable {
private:
    std::string d_texture;
    DWORD d_color;
public:
    TexturedQuad();

    void SetTexture(std::string texture);

    std::string GetTexture();

    SizeF *GetSize();

    void SetSize(SizeF * /* new GetSize */);

    void SetSize(float width, float height);

    Position *GetPosition();

    void SetPosition(Position * /* new GetPosition */);

    void SetPosition(float x, float y);

    SizeF *GetScale();

    void SetScale(SizeF *scale);

    SizeF *GetScaledSize();

    std::function<void(const uint8_t &, Position *)> OnMouseUp;
    std::function<void(const uint8_t &, Position *)> OnMouseDown;
    std::function<void(Position *)> OnMouseMove;
    std::function<void(const uint8_t &)> OnKeyUp;
    std::function<void(const uint8_t &)> OnKeyDown;

    DWORD GetColorARGB();
    void SetColorARGB(DWORD color);
};


#endif //HEADACHE_STATICDRAWABLE_H
