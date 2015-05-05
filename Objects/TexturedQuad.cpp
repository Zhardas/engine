#include "TexturedQuad.h"

void TexturedQuad::SetTexture(std::string texture) {
    _texture = texture;
}

std::string TexturedQuad::GetTexture() {
    return _texture;
}

Size TexturedQuad::GetSize() {
    return size_;
}

Position TexturedQuad::GetPosition() {
    return position_;
}

void TexturedQuad::SetSize(Size *size) {
    size_.width = size->width;
    size_.height = size->height;
}

void TexturedQuad::SetPosition(Position *position) {

    position_.x = position->x - Game::GetInstance()->g_width/2;
    position_.y = -position->y + Game::GetInstance()->g_height/2;
}

TexturedQuad::TexturedQuad() {

}
