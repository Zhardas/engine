class Interactive;
#ifndef OBJECTS_INTERFACES_INTERACTIVE_H_
#define OBJECTS_INTERFACES_INTERACTIVE_H_

#include <stdint.h>
#include <helper/types.h>
#include <functional>
#include <list>

class Interactive {
 public:
  std::list<std::function<bool(const uint8_t &, Position *)>> events_mouse_up_;
  std::list<std::function<bool(const uint8_t &, Position *)>> events_mouse_down_;
  std::list<std::function<bool(Position *)>> events_mouse_move_;
  std::list<std::function<bool(const uint8_t &)>> events_key_up_;
  std::list<std::function<bool(const uint8_t &)>> events_key_down_;

  bool MouseUp(const uint8_t &parameter, Position *position) {
    for (auto func : events_mouse_up_) {
      if (func(parameter, position))return true;
    }
    return false;
  }
  bool MouseDown(const uint8_t &parameter, Position *position) {
    for (auto func : events_mouse_down_) {
      if (func(parameter, position))return true;
    }
    return false;
  }
  bool MouseMove(Position *position) {
    for (auto func : events_mouse_move_) {
      if (func(position))return true;
    }
    return false;
  }
  bool KeyUp(const uint8_t &parameter) {
    for (auto func : events_key_up_) {
      if (func(parameter))return true;
    }
    return false;
  }
  bool KeyDown(const uint8_t &parameter) {
    for (auto func : events_key_down_) {
      if (func(parameter))return true;
    }
    return false;
  }
};


#endif  // OBJECTS_INTERFACES_INTERACTIVE_H_
