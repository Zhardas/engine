#include "textured_quad.h"

TexturedQuad::TexturedQuad() {
}
void TexturedQuad::CalcScaling() {
  size_scaled = Size(size_.width * scale_.width, size_.height * scale_.height);
}