class Combobox;

#ifndef OBJECTS_COMMON_COMBOBOX_H_
#define OBJECTS_COMMON_COMBOBOX_H_

#include <list>
#include "../textured_quad.h"
#include "./button.h"
#include "./combobox_item.h"

class Combobox: public TexturedQuad {
 private:
  std::list<ComboboxItem *> items_;
  bool items_visible_ = false;
 public:
  Button *button_ = new Button();
  Text *text_ = new Text();

  Combobox();

  void AddItem(ComboboxItem *item);
  void RemoveItem(ComboboxItem *item);

  virtual void set_size(float width, float height);
  virtual void set_position(float x, float y);
  void RefreshItemPositions();
  void RefreshItemVisibility();
};

#endif  // OBJECTS_COMMON_COMBOBOX_H_
