#include "layer.h"

Layer::Layer(Type type) {
  this->type_ = type;
  vertex_buffer_ = NULL;
}

bool Layer::EventCall(Event event, unsigned char key, Position *parameter) {
  for (std::list<Drawable *>::reverse_iterator rit = drawable_list_.rbegin(); rit != drawable_list_.rend(); ++rit) {
    if (auto obj = dynamic_cast<Interactive *>(*rit)) {
      switch (event) {
        case MOUSE_UP: {
          if (obj->MouseUp(key, parameter)) {
            return true;
          }
          break;
        }
        case MOUSE_DOWN: {
          if (obj->MouseDown(key, parameter)) {
            return true;
          }
          break;
        }
        case MOUSE_MOVE: {
          if (obj->MouseMove(parameter)) {
            return true;
          }
          break;
        }
        case KEYBOARD_UP: {
          if (obj->KeyUp(key)) {
            return true;
          }
          break;
        }
        case KEYBOARD_DOWN: {
          if (obj->KeyDown(key)) {
            return true;
          }
          break;
        }
      }
    }
  }
  return false;
}