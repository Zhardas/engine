#include "layer.h"

Layer::Layer(Type type) {
  this->type_ = type;
  vertex_buffer_ = NULL;
}

bool Layer::EventCall(Event event,
                      uint8_t key,
                      const Position &parameter,
                      std::shared_ptr<Drawable> drawable) {
  for (auto complex : drawable->complex_list_) {
    if (EventCall(event, key, parameter, complex))return true;
  }
  switch (event) {
    case MOUSE_UP: {
      if (drawable->MouseUp(key, parameter)) {
        return true;
      }
      break;
    }
    case MOUSE_DOWN: {
      if (drawable->MouseDown(key, parameter)) {
        return true;
      }
      break;
    }
    case MOUSE_MOVE: {
      if (drawable->MouseMove(parameter)) {
        return true;
      }
      break;
    }
    case KEYBOARD_UP: {
      if (drawable->KeyUp(key)) {
        return true;
      }
      break;
    }
    case KEYBOARD_DOWN: {
      if (drawable->KeyDown(key)) {
        return true;
      }
      break;
    }
  }
  return false;
}

bool Layer::EventCall(Event event, uint8_t key, const Position &parameter) {
  for (std::list<std::shared_ptr<Drawable>>::reverse_iterator rit = drawable_list_.rbegin();
       rit != drawable_list_.rend(); ++rit) {
    if (EventCall(event, key, parameter, *rit))return true;
  }
  return false;
}
void Layer::Add(std::shared_ptr<Drawable> obj) {
  obj->reload_layer_ = &reload_;
  drawable_list_.push_back(obj);
  reload_ = true;
}
void Layer::Remove(std::shared_ptr<Drawable> obj) {
  drawable_list_.remove(obj);
  reload_ = true;
}