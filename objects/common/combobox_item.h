class ComboboxItem;

#ifndef OBJECTS_COMMON_COMBOBOX_ITEM_H_
#define OBJECTS_COMMON_COMBOBOX_ITEM_H_

#include <string>
#include <objects/textured_quad.h>
#include <objects/text.h>

class ComboboxItem : public TexturedQuad {
 private:
 public:
  Text *text_ = new Text();

  explicit ComboboxItem(const std::string &text);

  void set_text(const std::string &text);
  virtual void set_size(float width, float height);
  virtual void set_position(float x, float y);
  virtual void set_visible(bool visible);
};


#endif //OBJECTS_COMMON_COMBOBOX_ITEM_H_
