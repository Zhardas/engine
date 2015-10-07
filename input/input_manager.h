class InputManager;
#ifndef INPUT_INPUT_MANAGER_H_
#define INPUT_INPUT_MANAGER_H_

#include <windows.h>
#include "game.h"
#include "helper/types.h"

class InputManager {
 private:
  Position mouse_position_;
 public:
  InputManager();
  void ParseMessage(UINT message, WPARAM parameter1, LPARAM parameter2);
  Position &mouse_position() {
    return mouse_position_;
  }
};


#endif  // INPUT_INPUT_MANAGER_H_
