#include "listbox.h"

Listbox::Listbox() {
  Add(button);
  set_texture("textbox.png");
  button->set_texture("listbox_button.png");
  set_size(256.0f, 32.0f);

  button->events_mouse_up_.push_back([this](const uint8_t &mbutton, const Position &pos) {
    bool item_clicked = false;
    if (mbutton == 0) {
      for (const auto &item : items_) {
        if (item->Contains(pos)) {
          item_clicked = true;
          break;
        }
      }
    }

    if (!item_clicked) {
      items_visible_ = false;
      RefreshItemVisibility();
    }
    return false;
  });
  button->events_onclick_.push_back([this]() {
    items_visible_ = !items_visible_;
    RefreshItemVisibility();
  });
}
void Listbox::set_size(float width, float height) {
  TexturedQuad::set_size(width, height);
  button->set_size(height, height);
  button->set_position(position_.x, position_.y);
}
void Listbox::set_position(float x, float y) {
  TexturedQuad::set_position(x, y);
  button->set_position(x, y);
}
void Listbox::add_item(Drawable *item) {
  item->set_visible(items_visible_);
  items_.push_back(item);
  Add(item);
  RefreshItemPositions();
}
void Listbox::remove_item(Drawable *item) {
  items_.remove(item);
  Remove(item);
  RefreshItemPositions();
}
void Listbox::RefreshItemPositions() {
  auto i = 0;
  for (const auto &item : items_) {
    i++;
    item->set_size(size_.width - size_.height, size_.height);
    item->set_position(position_.x + size_.height, position_.y - i * size_.height);
  }
}
void Listbox::RefreshItemVisibility() {
  for (const auto &item: items_) {
    item->set_visible(items_visible_);
  }
}
