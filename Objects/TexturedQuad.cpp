#include "TexturedQuad.h"

void TexturedQuad::SetTexture(std::string texture) {
    d_texture = texture;
}

std::string TexturedQuad::GetTexture() {
    return d_texture;
}

SizeF *TexturedQuad::GetSize() {
    return d_size;
}

Position *TexturedQuad::GetPosition() {
    return d_position;
}

void TexturedQuad::SetSize(SizeF *size) {
    SetSize(size->width, size->height);
    delete size;
}

void TexturedQuad::SetPosition(Position *position) {
    SetPosition(position->x, position->y);
    delete position;
}

TexturedQuad::TexturedQuad() {
    d_texture = "default.png";
    d_color = 0xffffffff;
}

void TexturedQuad::SetPosition(float x, float y) {
    d_position->x = x;// - Game::GetInstance()->g_width / 2;
    d_position->y = y;// + Game::GetInstance()->g_height / 2;
}

void TexturedQuad::SetSize(float width, float height) {
    d_size->width = width;
    d_size->height = height;
    d_scaledsize->width = width * d_scale->width;
    d_scaledsize->height = height * d_scale->height;
}

SizeF *TexturedQuad::GetScale() {
    return Drawable::GetScale();
}

void TexturedQuad::SetScale(SizeF *scale) {
    Drawable::SetScale(scale);
}

SizeF *TexturedQuad::GetScaledSize() {
    return Drawable::GetScaledSize();
}

DWORD TexturedQuad::GetColorARGB() {
    return d_color;
}
void TexturedQuad::SetColorARGB(DWORD color) {
    d_color = color;
}
