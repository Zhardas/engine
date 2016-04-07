class Listbox;

#ifndef OBJECTS_COMMON_LISTBOX_H_
#define OBJECTS_COMMON_LISTBOX_H_

#include <objects/textured_quad.h>
#include "button.h"

class Listbox: public TexturedQuad {
 private:
  std::list<Drawable *> items_;
  bool items_visible_ = false;
 public:
  Button *button = new Button();

  Listbox();

  void add_item(Drawable *drawable);
  void remove_item(Drawable *item);

  virtual void set_size(float width, float height);
  virtual void set_position(float x, float y);
  void RefreshItemPositions();
  void RefreshItemVisibility();
};


#endif //OBJECTS_COMMON_LISTBOX_H_
