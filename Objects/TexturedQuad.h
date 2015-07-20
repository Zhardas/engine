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

    void CalcScaling() {
        d_size_scaled = SizeF(d_size.width * d_scale.width, d_size.height * d_scale.height);
    }

public:
    TexturedQuad();

    void SetTexture(std::string texture) {
        d_texture = texture;
    }

    std::string GetTexture() {
        return d_texture;
    }

    SizeF GetSize() {
        return d_size;
    }

    void SetSize(SizeF size) {
        d_size.width = size.width;
        d_size.height = size.height;
        CalcScaling();
    }

    void SetSize(float width, float height) {
        d_size.width = width;
        d_size.height = height;
        CalcScaling();
    }

    Position GetPosition() {
        return d_position;
    }

    void SetPosition(Position position) {
        d_position.x = position.x;
        d_position.y = position.y;
    }

    void SetPosition(float x, float y) {
        d_position.x = x;
        d_position.y = y;
    }

    SizeF GetScale() {
        return d_scale;
    }

    void SetScale(SizeF scale) {
        d_scale.width = scale.width;
        d_scale.height = scale.height;
        CalcScaling();
    }

    SizeF GetScaledSize() {
        return d_size_scaled;
    }

    void SetRotation(float rot) {
        Drawable::SetRotation(rot);
    }

    float GetRotation() {
        return Drawable::GetRotation();
    }

    bool Contains(Position *pos) {
        return pos->x >= d_position.x - d_size_scaled.width / 2 &&
               pos->x <= d_position.x + d_size_scaled.width / 2 &&
               pos->y >= d_position.y - d_size_scaled.height / 2 &&
               pos->y <= d_position.y + d_size_scaled.height / 2;
    }

    std::function<void(const uint8_t &, Position *)> OnMouseUp;
    std::function<void(const uint8_t &, Position *)> OnMouseDown;
    std::function<void(Position *)> OnMouseMove;
    std::function<void(const uint8_t &)> OnKeyUp;
    std::function<void(const uint8_t &)> OnKeyDown;

    DWORD GetColorARGB() {
        return d_color;
    }

    void SetColorARGB(DWORD color) {
        d_color = color;
    }
};


#endif //HEADACHE_STATICDRAWABLE_H
