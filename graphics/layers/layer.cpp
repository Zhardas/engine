#include "layer.h"

Layer::Layer(Type type) {
  this->type_ = type;
  vertex_buffer_ = NULL;
}

bool Layer::EventCall(Event event,
                      uint8_t key,
                      const Position &parameter,
                      Drawable *drawable) {
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
  if (drawable->is_complex_) {
    for (const auto &complex : drawable->complex_list_) {
      if (EventCall(event, key, parameter, complex.get()))return true;
    }
  }
  return false;
}

bool Layer::EventCall(Event event, uint8_t key, const Position &parameter) {
  for (std::list<std::unique_ptr<Drawable>>::reverse_iterator rit = drawable_list_.rbegin();
       rit != drawable_list_.rend(); ++rit) {
    if (EventCall(event, key, parameter, rit->get()))return true;
  }
  return false;
}
void Layer::Add(Drawable *obj) {
  obj->set_reload_ptr(&reload_);
  drawable_list_.push_back(std::unique_ptr<Drawable>(obj));
  reload_ = true;
}
void Layer::Remove(Drawable *obj) {
  drawable_list_.remove_if([obj](const std::unique_ptr<Drawable> &ptr) {
    return ptr.get() == obj;
  });
  reload_ = true;
}
