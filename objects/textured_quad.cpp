#include "textured_quad.h"

void TexturedQuad::CalcScaling() {
  size_scaled = Size(size_.width * scale_.width, size_.height * scale_.height);
}
void TexturedQuad::Draw(Renderer *renderer, uint32_t *index) {
  if (visible())renderer->DrawTexture(index, texture());
  (*index)++;
}
void TexturedQuad::PrepareVertices(Renderer *renderer, v_3ct *vertices, uint32_t *index) {
  vertices[(*index) * 4] = {0.0f, 0.0f, 0.0f, color_[3], 0.0f, 1.0f};
  vertices[(*index) * 4 + 1] = {0.0f, size().height, 0.0f, color_[0], 0.0f, 0.0f};
  vertices[(*index) * 4 + 2] = {size().width, 0.0f, 0.0f, color_[2], 1.0f, 1.0f};
  vertices[(*index) * 4 + 3] =
      {size().width, size().height, 0.0f, color_[1], 1.0f, 0.0f};
  (*index)++;
}
void TexturedQuad::Update() {
  if (!animated_ || remove_)return;
  animation_timer_ = (animation_timer_ + 1) % animation_speed_;
  if (animation_timer_ == 0) {
    texture_index_current_ = (texture_index_current_ + 1) % (texture_index_end_ + 1);
    if (texture_index_current_ == 0){
      if (destroy_after_animation_) {
        remove_ = true;
        return;
      }
      texture_index_current_ = texture_index_start_;
    }
    texture_ = texture_base_ + std::to_string(texture_index_current_) + ".png";
  }
  Drawable::Update();
}