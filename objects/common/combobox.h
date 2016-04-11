class Combobox;

#ifndef OBJECTS_COMMON_COMBOBOX_H_
#define OBJECTS_COMMON_COMBOBOX_H_

#include <list>
#include "../textured_quad.h"
#include "./button.h"

class Combobox: public TexturedQuad {
 private:
  std::list<Drawable *> items_;
  bool items_visible_ = false;
 public:
  Button *button = new Button();

  Combobox();

  void AddItem(Drawable *drawable);
  void RemoveItem(Drawable *item);

  virtual void set_size(float width, float height);
  virtual void set_position(float x, float y);
  void RefreshItemPositions();
  void RefreshItemVisibility();
};

#endif  // OBJECTS_COMMON_COMBOBOX_H_
