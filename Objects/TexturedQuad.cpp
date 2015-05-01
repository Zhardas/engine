#include "TexturedQuad.h"

void TexturedQuad::SetTexture(std::string texture) {
    _texture = texture;
}

std::string TexturedQuad::GetTexture() {
    return _texture;
}

Size TexturedQuad::size() {
    return size_;
}

Position TexturedQuad::position() {
    return position_;
}

void TexturedQuad::set_size(Size *size) {
    size_.width = size->width;
    size_.height = size->height;
}

void TexturedQuad::set_position(Position *position) {
    position_.x = position->x;
    position_.y = position->y;
}

TexturedQuad::TexturedQuad() {

}
