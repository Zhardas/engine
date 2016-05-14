#include "combobox.h"

Combobox::Combobox() {
  text_->set_text("");
  Add(text_);
  text_->color_red_ = 0;
  text_->color_green_ = 0;
  text_->color_blue_ = 0;
  Add(button_);
  set_texture("box.png");
  button_->set_texture("listbox_button.png");
  set_size(110.0f, 23.0f);

  button_->events_mouse_up_.push_back([this](const uint8_t &mbutton, const Position &pos) {
    auto clicked = false;
    if (mbutton == 0) {
      for (const auto &item : items_) {
        if (item->Contains(pos) && items_visible_) {
          clicked = true;
          text_->set_text(item->text_->text());
          break;
        }
      }
    }
    items_visible_ = false;
    RefreshItemVisibility();
    return clicked;
  });
  button_->events_onclick_.push_back([this]() {
    items_visible_ = !items_visible_;
    RefreshItemVisibility();
  });
}
void Combobox::set_size(float width, float height) {
  TexturedQuad::set_size(width, height);
  button_->set_size((height - 4.0f) / 19.0f * 17.0f, height - 4.0f);
  button_->set_position(position_.x + width - button_->size().width - 2.0f, position_.y + 2.0f);
  text_->set_position(position_.x, position_.y + size_.height);
}
void Combobox::set_position(float x, float y) {
  TexturedQuad::set_position(x, y);
  button_->set_position(position_.x + size().width - button_->size().width - 2.0f, position_.y + 2.0f);
  text_->set_position(position_.x, position_.y + size_.height);
}
void Combobox::AddItem(ComboboxItem *item) {
  item->set_visible(items_visible_);
  items_.push_back(item);
  Add(item);
  RefreshItemPositions();
}
void Combobox::RemoveItem(ComboboxItem *item) {
  items_.remove(item);
  Remove(item);
  RefreshItemPositions();
}
void Combobox::RefreshItemPositions() {
  auto i = 0;
  for (const auto &item : items_) {
    i++;
    item->set_size(size_.width - button_->size().width, size_.height);
    item->set_position(position_.x, position_.y - i * size_.height);
  }
}
void Combobox::RefreshItemVisibility() {
  for (const auto &item: items_) {
    item->set_visible(items_visible_);
  }
}
