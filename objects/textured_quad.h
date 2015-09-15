class TexturedQuad;

#ifndef HEADACHE_STATICDRAWABLE_H
#define HEADACHE_STATICDRAWABLE_H

#include "drawable.h"
#include "game.h"
#include <string>
#include <functional>

class TexturedQuad: Drawable {
private:
    void CalcScaling() {
        size_scaled = SizeF(size_.width * scale_.width, size_.height * scale_.height);
    }

protected:
    std::string texture_;
    DWORD color_;
public:
    TexturedQuad();

    void set_texture(std::string texture) {
        texture_ = texture;
    }

    std::string texture() {
        return texture_;
    }

    SizeF size() {
        return size_;
    }

    void set_size(SizeF size) {
        size_.width = size.width;
        size_.height = size.height;
        CalcScaling();
    }

    void set_size(float width, float height) {
        size_.width = width;
        size_.height = height;
        CalcScaling();
    }

    Position position() {
        return position_;
    }

    void set_position(Position position) {
        position_.x = position.x;
        position_.y = position.y;
    }

    void set_position(float x, float y) {
        position_.x = x;
        position_.y = y;
    }

    SizeF scale() {
        return scale_;
    }

    void set_scaled_size(SizeF scale) {
        scale_.width = scale.width;
        scale_.height = scale.height;
        CalcScaling();
    }

    SizeF scaled_size() {
        return size_scaled;
    }

    void set_rotation(float rot) {
        Drawable::set_rotation(rot);
    }

    float rotation() {
        return Drawable::rotation();
    }

    bool Contains(Position pos) {
        return Drawable::Contains(pos);
    }

    std::function<bool(const uint8_t &, Position *)> OnMouseUp;
    std::function<bool(const uint8_t &, Position *)> OnMouseDown;
    std::function<bool(Position *)> OnMouseMove;
    std::function<bool(const uint8_t &)> OnKeyUp;
    std::function<bool(const uint8_t &)> OnKeyDown;

    DWORD color() {
        return color_;
    }

    void set_color(DWORD color) {
        color_ = color;
    }
};


#endif //HEADACHE_STATICDRAWABLE_H
