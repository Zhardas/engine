#include "TexturedQuad.h"

void TexturedQuad::SetTexture(std::string texture) {
    d_texture = texture;
}

std::string TexturedQuad::GetTexture() {
    return d_texture;
}

Size *TexturedQuad::GetSize() {
    return d_size;
}

Position *TexturedQuad::GetPosition() {
    return d_position;
}

void TexturedQuad::SetSize(Size *size) {
    SetSize(size->width, size->height);
    delete size;
}

void TexturedQuad::SetPosition(Position *position) {
    SetPosition(position->x, position->y);
    delete position;
}

TexturedQuad::TexturedQuad() {
    d_texture = "default.png";
}

void TexturedQuad::SetPosition(int x, int y) {
    d_position->x = x - Game::GetInstance()->g_width / 2;
    d_position->y = -y + Game::GetInstance()->g_height / 2;
}

void TexturedQuad::SetSize(int width, int height) {
    d_size->width = width;
    d_size->height = height;
    d_scaledsize->width = static_cast<int>(width * d_scale->width);
    d_scaledsize->height = static_cast<int>(height * d_scale->height);
}

SizeF *TexturedQuad::GetScale() {
    return Drawable::GetScale();
}

void TexturedQuad::SetScale(SizeF *scale) {
    Drawable::SetScale(scale);
}

Size *TexturedQuad::GetScaledSize() {
    return Drawable::GetScaledSize();
}
